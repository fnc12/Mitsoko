
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__HORIZONTAL_SCROLL_VIEW__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__HORIZONTAL_SCROLL_VIEW__

#include "FrameLayout.hpp"

namespace android{
    
    namespace widget{
        
        struct HorizontalScrollView:public FrameLayout{
            
            using FrameLayout::FrameLayout;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/HorizontalScrollView");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__HORIZONTAL_SCROLL_VIEW__
