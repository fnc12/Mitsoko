
#ifndef __VIPER__IOS_UTIL__UI__IMAGE_VIEW__
#define __VIPER__IOS_UTIL__UI__IMAGE_VIEW__

#include "View.hpp"
#include "Image.hpp"

namespace UI {
    struct ImageView:public UI::View{
        using View::View;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(std::string, className, "UIImageView");
        
        void setImage(const UI::Image &newValue);
        
        UI::Image image();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__IMAGE_VIEW__
