
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace java{
    namespace util{
        struct Locale final : public java::lang::Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/util/Locale");
#ifdef __ANDROID__
            void start(){
                this->sendMessage<void>("start");
            }
            
            java::lang::String getLanguage(){
                return this->sendMessage<java::lang::String>("getLanguage");
            }
            
            static Locale getDefault(){
                if(auto java_env=java::lang::JNI::Env()){
                    auto clazz = java_env->FindClass(signature().c_str());
                    auto mid=java_env->GetStaticMethodID(clazz,"getDefault",generateMethodSignature<Locale>().c_str());
//                    return java_env->NewObject(clazz, ctor, runnable);
                    return java_env->CallStaticObjectMethod(clazz,mid);
                }else{
                    return {};
                }
            }
#endif
        };
    }
}
