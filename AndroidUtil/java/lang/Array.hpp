
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__ARRAY__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__ARRAY__

#include "JNI.hpp"

#ifdef __ANDROID__
#include <jni.h>
#endif

namespace java{
    
    namespace lang{
        
        /**
         *  This class doesn't exist in java actually. This is 
         *  a java array binding T[].
         */
        template<class T>
        struct Array {
#ifdef __ANDROID__
            typedef void *Handle;
            Handle handle;
            
            Array(Handle h):handle(h){}
            Array():Array(nullptr){}
            
            static Array<T> create(int size, const T &initialElement){
                if(auto env = java::lang::JNI::Env()){
                    auto handle = env->NewObjectArray(size,
                                                      env->FindClass(T::signature.c_str()),
                                                      (jobject)initialElement.handle);
                    return handle;
                }else{
                    return {};
                }
            }
            
            struct ElementProxy {
                Array<T> &array;
                const int index;
                
                void operator=(const T &value) {
                    if(auto env = java::lang::JNI::Env()) {
                        env->SetObjectArrayElement(jobjectArray(array.handle),
                                                   this->index,
                                                   (jobject)value.handle);
                    }else{
                        //..
                    }
                }
            };
            
            ElementProxy operator[](int index){
                return ElementProxy{*this, index};
            }
#endif  //__ANDROID__
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__ARRAY__
