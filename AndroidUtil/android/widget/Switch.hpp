
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__SWITCH__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__SWITCH__

#include "CompoundButton.hpp"

namespace android{
    
    namespace widget{
        
        struct Switch : public CompoundButton {
            
            using CompoundButton::CompoundButton;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/widget/Switch");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__SWITCH__
