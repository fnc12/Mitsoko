
#ifndef __Mitsoko__ios_util__ui__textField__
#define __Mitsoko__ios_util__ui__textField__

#include "Control.hpp"
#include "TextInput.hpp"
#include "Mitsoko/iOSutil/CF/String.hpp"

namespace UI {
    
    struct TextField : public virtual UI::Control, public virtual UI::TextInput {
        
#ifdef __APPLE__
        static const std::string className;
        
        TextField();
        
        TextField(Handle handle);
        
        void setText(const std::string &newValue);
        
        std::string text();
        
        void setPlaceholder(const std::string &newValue);
        
        std::string placeholder();
        
    private:
        typedef UI::Control Super;
#endif
    };
}

#endif  //__Mitsoko__ios_util__ui__textField__
