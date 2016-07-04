
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace android{
    namespace view{
        struct MenuItem:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/view/MenuItem");
            
            MenuItem& setTitle(const std::string &title){
                auto str=java::lang::String::create(title);
                return this->setTitle(str);
            }
            
            MenuItem& setTitle(const java::lang::CharSequence &title){
                this->sendMessage<MenuItem>("setTitle",title);
                return *this;
            }
            
            std::string getTitle(){
                return this->sendMessage<java::lang::CharSequence>("getTitle").toString().c_str();
            }
#endif
        };
    }
}
