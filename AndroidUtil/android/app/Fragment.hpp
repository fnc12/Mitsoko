
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Activity.hpp"

namespace android{
    namespace app{
        struct Fragment:public java::lang::Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "android/app/Fragment");
#ifdef __ANDROID__
            Activity getActivity(){
                return this->sendMessage<Activity>("getActivity");
            }
#endif
        };
    }
}
