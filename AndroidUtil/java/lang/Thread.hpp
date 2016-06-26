
#pragma once

#include "Object.hpp"
#include "Runnable.hpp"

namespace java{
    namespace lang{
        struct Thread:public Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/lang/Thread");
            
            void start(){
                this->sendMessage<void>("start");
            }
            
            static Thread create(const Runnable &runnable){
                return java::lang::Object::create<Thread>(runnable);
                /*if(auto java_env=java::lang::JNI::Env()){
                    jclass clazz = java_env->FindClass(signature().c_str());
                    jmethodID ctor=java_env->GetMethodID(clazz,"<init>",generateMethodSignature<void,Runnable>().c_str());
                    return java_env->NewObject(clazz, ctor, runnable);
                }else{
                    return nullptr;
                }*/
            }
#endif
        };
    }
}
