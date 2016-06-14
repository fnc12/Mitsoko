
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace widget{
        struct Adapter:public java::lang::Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "android/widget/Adapter");
        };
    }
}
