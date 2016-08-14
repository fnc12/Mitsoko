
#ifndef __VIPER__IOS_UTIL__UI__TEXT_FIELD__
#define __VIPER__IOS_UTIL__UI__TEXT_FIELD__

#include "Control.hpp"
#include "TextInput.hpp"
#include "Viper/iOSutil/CF/String.hpp"

namespace UI {
    struct TextField:public virtual UI::Control, public virtual UI::TextInput{
        
#ifdef __APPLE__
        TextField();
        
        TextField(Handle handle);
        
        typedef UI::Control Super;
        
        void setText(const std::string &newValue);
        
        void setText(const CF::String &newValue);
        
        std::string text();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__TEXT_FIELD__
