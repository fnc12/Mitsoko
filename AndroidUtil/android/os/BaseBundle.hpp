
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace android{
    namespace os{
        struct BaseBundle:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/os/BaseBundle");
            
            java::lang::Object get(const char *key){
                return std::move(this->get(std::string(key)));
            }
            
            java::lang::Object get(const std::string &key){
                auto s=java::lang::String::create(key);
                return std::move(this->get(s));
            }
            
            java::lang::Object get(const java::lang::String &key){
                return this->sendMessage<java::lang::Object>("get",key);
            }
#endif
        };
    }
}
