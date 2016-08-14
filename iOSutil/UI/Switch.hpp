
#ifndef __VIPER__IOS_UTIL__UI__SWITCH__
#define __VIPER__IOS_UTIL__UI__SWITCH__

#include "Control.hpp"

namespace UI {
    struct Switch:public UI::Control{
        using Control::Control;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        void setOn(bool newValue);
        
        bool on();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__SWITCH__
