
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        struct Thread:public Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/lang/Thread");
#ifdef __ANDROID__
            void start(){
                this->sendMessage<void>("start");
            }
            
            static Thread create(jobject runnable){
                if(auto java_env=java::lang::JNI::Env()){
                    jclass clazz = java_env->FindClass(signature().c_str());
                    jmethodID ctor=java_env->GetMethodID(clazz,"<init>",generateMethodSignature<void,Runnable>().c_str());
                    return java_env->NewObject(clazz, ctor, runnable);
                }else{
                    return nullptr;
                }
            }
#endif
        };
    }
}
