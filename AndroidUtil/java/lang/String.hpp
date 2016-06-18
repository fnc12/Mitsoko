
#pragma once

#include "Object.hpp"
#include "CharSequence.hpp"

namespace java{
    namespace lang{
        struct String:public _CharSequence<String>{
            using _CharSequence::_CharSequence;
            STATIC_VAR(const std::string, signature, "java/lang/String");
#ifdef __ANDROID__
            const char* c_str()const{
                if(auto env=JNI::Env()){
                    return env->GetStringUTFChars(static_cast<jstring>(const_cast<void*>(this->handle)), JNI_FALSE);
                }else{
                    return nullptr;
                }
            }
            
            static String create(std::string str){
                if(auto env=JNI::Env()){
                    jbyteArray array = env->NewByteArray(str.size());
                    env->SetByteArrayRegion(array, 0, str.size(), (const jbyte*)str.c_str());
                    jstring strEncode = env->NewStringUTF("UTF-8");
                    jclass cls = env->FindClass(signature().c_str());
                    jmethodID ctor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;)V");
                    jstring object = (jstring) env->NewObject(cls, ctor, array, strEncode);
                    return object;
                }else{
                    return nullptr;
                }
            }
#endif
        };
        typedef _CharSequence<String> CharSequence;
    }
}
