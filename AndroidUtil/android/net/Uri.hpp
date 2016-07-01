
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android {
    namespace net{
        struct Uri:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/net/Uri");
            
#endif
        };
    }
}
