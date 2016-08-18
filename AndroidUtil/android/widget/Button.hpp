
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__BUTTON__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__BUTTON__

#include "TextView.hpp"

namespace android{
    
    namespace widget{
        
        struct Button:public TextView{
            
            using TextView::TextView;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/Button");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__BUTTON__
