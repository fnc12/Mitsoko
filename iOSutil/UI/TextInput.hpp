
#pragma once

#include "TextInputTraits.hpp"

namespace UI {
    
    /**
     *  Protocol.
     */
    struct KeyInput:public UI::TextInputTraits{
        using TextInputTraits::TextInputTraits;
#ifdef __APPLE__
        
#endif
    };
    
    /**
     *  Protocol.
     */
    struct TextInput:public UI::KeyInput{
        using KeyInput::KeyInput;
        
    };
}
