
#pragma once

#include <sstream>
#include <string>
#include <vector>

#ifdef __ANDROID__
#include <jni.h>
#include "Array.hpp"
#endif

#ifdef __ANDROID__
template<class T>
struct TypeSignatureGenerator{
    std::string operator()()const{
        std::stringstream ss;
        ss<<"L"<<T::signature()<<";";
        return std::move(ss.str());
    }
};

#define TYPE_SIGNATURE(t,s) template<> struct TypeSignatureGenerator<t>{std::string operator()()const{return s;}};
TYPE_SIGNATURE(void,"V");
TYPE_SIGNATURE(int,"I");
TYPE_SIGNATURE(bool,"Z");
TYPE_SIGNATURE(double,"D");
#undef TYPE_SIGNATURE

//  array specialization..
template<class T>
struct TypeSignatureGenerator<java::lang::Array<T>>{
    std::string operator()()const{
        return "["+TypeSignatureGenerator<T>()();
    }
};

template<class ...Args>
struct SignatureGenerator;

template<class T,class ...Args>
struct SignatureGenerator<T,Args...>{
    std::string operator()()const{
        std::stringstream ss;
        ss<<TypeSignatureGenerator<T>()()<<SignatureGenerator<Args...>()();
        return std::move(ss.str());
    }
};

template<>
struct SignatureGenerator<>{
    std::string operator()()const{
        return {};
    }
};

/**
 *  ArgumentProxy is a class translating c++ type to
 *  java (jni) type. It casts double to jdouble,
 *  bool to jboolean, int to jint and any other types
 *  to jobject.
 */
template<class T>
struct ArgumentProxy{
    static jobject cast(const T &value){
        return static_cast<jobject>(const_cast<void*>(value.handle));
    }
};

template<>
struct ArgumentProxy<double>{
    static jdouble cast(const double &value){
        return jdouble(value);
    }
};

template<>
struct ArgumentProxy<bool>{
    static jboolean cast(const bool &value){
        return jboolean(value);
    }
};

template<>
struct ArgumentProxy<int>{
    static jint cast(const int &value){
        return jint(value);
    }
};

/*template<class T>
struct ArgumentProxy<std::vector<T>>{
    static jobjectArray cast(const std::vector<T> &value){
        return jobjectArray(value);
    }
};*/

template<class RT>
struct MessageSender{
    template<class ...Args>
    jobject operator()(JNIEnv *java_env,jobject receiver,jmethodID methodId,const Args& ...args)const{
        return java_env->CallObjectMethod(receiver,methodId,ArgumentProxy<Args>::cast(args)...);
    }
    jobject failure()const{
        return nullptr;
    }
};

template<>
struct MessageSender<void>{
    template<class ...Args>
    void operator()(JNIEnv *java_env,jobject receiver,jmethodID methodId,const Args& ...args)const{
        java_env->CallVoidMethod(receiver,methodId,ArgumentProxy<Args>::cast(args)...);
    }
    void failure()const{}
};

template<>
struct MessageSender<bool>{
    template<class ...Args>
    bool operator()(JNIEnv *java_env,jobject receiver,jmethodID methodId,const Args& ...args)const{
        return java_env->CallBooleanMethod(receiver,methodId,ArgumentProxy<Args>::cast(args)...);
    }
    bool failure()const{
        return false;
    }
};

template<>
struct MessageSender<int>{
    template<class ...Args>
    int operator()(JNIEnv *java_env,jobject receiver,jmethodID methodId,const Args& ...args)const{
        return java_env->CallIntMethod(receiver,methodId,ArgumentProxy<Args>::cast(args)...);
    }
    int failure()const{
        return -1;
    }
};

template<>
struct MessageSender<double>{
    template<class ...Args>
    double operator()(JNIEnv *java_env,jobject receiver,jmethodID methodId,const Args& ...args)const{
        return java_env->CallDoubleMethod(receiver,methodId,ArgumentProxy<Args>::cast(args)...);
    }
    double failure()const{
        return -1;
    }
};
#endif
