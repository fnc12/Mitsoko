
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace os{
        struct Handler:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/os/Handler");
            
            bool post(const java::lang::Runnable &runnable){
                return this->sendMessage<bool>("post",runnable);
            }
            
            static Handler create(){
                if(auto java_env=java::lang::JNI::Env()){
                    if(auto clazz=java_env->FindClass(signature().c_str())){
                        if(auto ctor = java_env->GetMethodID(clazz, "<init>", "()V")){
                            return java_env->NewObject(clazz, ctor);
                        }else{
                            return nullptr;
                        }
                    }else{
                        return nullptr;
                    }
                }else{
                    return nullptr;
                }
            }
#endif
        };
    }
}
