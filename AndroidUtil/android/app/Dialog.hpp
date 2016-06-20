
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/android/view/Window.hpp"

namespace android{
    namespace app{
        struct Dialog:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/Dialog");
            
            view::Window getWindow(){
                return this->sendMessage<view::Window>("getWindow");
            }
#endif
        };
    }
}
