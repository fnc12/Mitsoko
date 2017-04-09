
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__CHECK_BOX__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__CHECK_BOX__

#include "CompoundButton.hpp"

namespace android{
    
    namespace widget{
        
        struct CheckBox : public CompoundButton {
            
            using CompoundButton::CompoundButton;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/widget/CheckBox");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__CHECK_BOX__
