
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__TAB_HOST__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__TAB_HOST__

#include "FrameLayout.hpp"

namespace android{
    
    namespace widget{
        
        struct TabHost:public FrameLayout{
            
            using FrameLayout::FrameLayout;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/TabHost");
            
            int getCurrentTab();
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__TAB_HOST__
