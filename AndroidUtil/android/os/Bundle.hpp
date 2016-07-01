
#pragma once

#include "BaseBundle.hpp"

namespace android{
    namespace os{
        struct Bundle:public BaseBundle{
            using BaseBundle::BaseBundle;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/os/Bundle");
            
#endif
        };
    }
}

