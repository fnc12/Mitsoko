
#ifndef __VIPER__IOS_UTIL__UI__TEXT_INPUT__
#define __VIPER__IOS_UTIL__UI__TEXT_INPUT__

#include "TextInputTraits.hpp"

namespace UI {
    
    /**
     *  Protocol.
     */
    struct KeyInput : public UI::TextInputTraits {
        using TextInputTraits::TextInputTraits;
#ifdef __APPLE__
        
#endif
    };
    
    /**
     *  Protocol.
     */
    struct TextInput : public UI::KeyInput {
        using KeyInput::KeyInput;
        
    };
}

#endif  //__VIPER__IOS_UTIL__UI__TEXT_INPUT__
