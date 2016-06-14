
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace content{
        struct Intent:public java::lang::Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "android/content/Intent");
#ifdef __ANDROID__
            static jobject create(const Context &context,const java::lang::Class &cls){
                if(auto java_env=java::lang::JNI::Env()){
                    if(auto intentClass=java_env->FindClass(signature().c_str())){
                        if(auto newIntent = java_env->GetMethodID(intentClass, "<init>", "(Landroid/content/Context;Ljava/lang/Class;)V")){
                            return java_env->NewObject(intentClass, newIntent,context.handle,cls.handle);
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
            
            Intent& putExtra(const std::string &name,const std::string &value){
                auto j_name=java::lang::String::create(name);
                auto j_value=java::lang::String::create(value);
                this->sendMessage<Intent>("putExtra",j_name,j_value);
                return *this;
            }
#endif
        };
    }
}
