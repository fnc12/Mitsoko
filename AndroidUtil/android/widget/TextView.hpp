
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__TEXT_VIEW__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__TEXT_VIEW__

#include "Viper/AndroidUtil/android/view/View.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Viper/AndroidUtil/android/graphics/Color.hpp"

namespace android{
    
    namespace widget{
        
        struct TextView:public view::View{
            
            using View::View;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/TextView");
            
            void setInputType(int type);
            
            void setTextColor(int color);
            
            void setText(const std::string &value);
            
            void setText(const java::lang::String &str);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__TEXT_VIEW__
