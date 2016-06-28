
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace android{
    namespace support{
        namespace v7{
            namespace app{
                struct ActionBar:public java::lang::Object{
                    using Object::Object;
#ifdef __ANDROID__
                    STATIC_VAR(const std::string, signature, "android/support/v7/app/ActionBar");
                    
                    java::lang::CharSequence getTitle(){
                        return this->sendMessage<java::lang::CharSequence>("getTitle");
                    }
                    
                    void setTitle(const std::string &title){
                        auto t=java::lang::String::create(title);
                        this->setTitle(t);
                    }
                    
                    void setTitle(const java::lang::CharSequence &title){
                        this->sendMessage<void>("setTitle",title);
                    }
                    
                    void hide(){
                        this->sendMessage<void>("hide");
                    }
#endif
                };
            }
        }
    }
}
