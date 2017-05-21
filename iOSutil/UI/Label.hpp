
#ifndef __VIPER__IOS_UTIL__UI__LABEL__
#define __VIPER__IOS_UTIL__UI__LABEL__

#include "View.hpp"
#include "Mitsoko/iOSutil/UI/Color.hpp"
#include "Mitsoko/iOSutil/CF/String.hpp"
#include "Mitsoko/Util.hpp"
#include "Mitsoko/iOSutil/NS/TextAlignment.hpp"

namespace UI {
    
    struct Label : public UI::View {
        
        using View::View;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        void setText(const std::string &newValue);
        
        void setTextColor(const UI::Color &newValue);
        
        UI::Color textColor();
        
        void setTextAlignment(NS::TextAlignment value);
        
        NS::TextAlignment textAlignment();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__LABEL__
