
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace content{
        namespace res{
            struct Resources:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/content/res/Resources");
#ifdef __ANDROID__
                /*int getIdentifier(const std::string &name,const std::string &defType,const java::lang::String &defPackage){
                 java::lang::String n=java::lang::String::create(name);
                 LOGI("n = *%s*",n.c_str());
                 java::lang::String t=java::lang::String::create(defType);
                 LOGI("t = *%s*",t.c_str());
                 //                    Java::lang::String p=Java::lang::String::create(defPackage);
                 this->sendMessage<jint>("getIdentifier",n,t,defPackage);
                 }*/
#endif
            };
        }
    }
}
