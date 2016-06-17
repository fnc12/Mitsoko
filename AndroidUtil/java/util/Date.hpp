
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace java{
    namespace util{
        struct Date:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/util/Date");
            
            static Date create(long milliseconds){
                if(auto java_env=java::lang::JNI::Env()){
                    if(auto clazz=java_env->FindClass(signature().c_str())){
                        if(auto ctor = java_env->GetMethodID(clazz, "<init>", "(J)V")){
                            return java_env->NewObject(clazz, ctor, jlong(milliseconds));
                        }else{
                            return {};
                        }
                    }else{
                        return {};
                    }
                }else{
                    return {};
                }
            }
#endif
        };
    }
}