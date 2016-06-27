
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace support{
        namespace v7{
            namespace app{
                struct ActionBar:public java::lang::Object{
                    using Object::Object;
#ifdef __ANDROID__
                    STATIC_VAR(const std::string, signature, "android/support/v7/app/ActionBar");
                    
                    void hide(){
                        this->sendMessage<void>("hide");
                    }
#endif
                };
            }
        }
    }
}
