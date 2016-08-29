
#ifndef __VIPER__IOS_UTIL__UI__BUTTON__
#define __VIPER__IOS_UTIL__UI__BUTTON__

#include "Control.hpp"
#include "Viper/iOSutil/CF/String.hpp"

namespace UI {
    
    struct Button:public UI::Control{
        
        using Control::Control;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        void setTitle(const std::string &title,UI::Control::State state);

#endif  //__APPLE__
        
    };
}

#endif  //__VIPER__IOS_UTIL__UI__BUTTON__
