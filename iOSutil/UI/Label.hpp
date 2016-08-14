
#ifndef __VIPER__IOS_UTIL__UI__LABEL__
#define __VIPER__IOS_UTIL__UI__LABEL__

#include "View.hpp"
#include "Viper/iOSutil/UI/Color.hpp"
#include "Viper/iOSutil/CF/String.hpp"
#include "Viper/Util.hpp"

namespace UI {
    struct Label:public UI::View{
        using View::View;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UILabel");
        
        void setText(const std::string &newValue);
        
        void setTextColor(const UI::Color &newValue);
        
        UI::Color textColor();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__LABEL__
