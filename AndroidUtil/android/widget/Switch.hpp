
#pragma once

#include "CompoundButton.hpp"

namespace android{
    namespace widget{
        struct Switch:public CompoundButton{
            using CompoundButton::CompoundButton;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/Switch");
            
#endif
            
        };
    }
}
