
#ifndef __VIPER__IOS_UTIL__UI__TEXTVIEW__
#define __VIPER__IOS_UTIL__UI__TEXTVIEW__

#include "ScrollView.hpp"
#include "Viper/Util.hpp"
#include "Viper/iOSutil/CF/String.hpp"

namespace UI {
    struct TextView:public UI::ScrollView{
        using ScrollView::ScrollView;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UITextView");
        
        void setText(const CF::String &newValue);
        
        void setText(const std::string &newValue);
        
        std::string text();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__TEXTVIEW__
