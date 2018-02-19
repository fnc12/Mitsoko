
#ifndef __MITSOKO__IOS_UTIL__UI__BUTTON__
#define __MITSOKO__IOS_UTIL__UI__BUTTON__

#include "Control.hpp"
#include "Mitsoko/iOSutil/CF/String.hpp"
#include "Mitsoko/iOSutil/UI/Color.hpp"
#include "Image.hpp"

namespace UI {
    
    struct Button : public UI::Control {
        
        using Control::Control;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        void setTitle(const std::string &title, UI::Control::State state);
        
        void setTitleColor(UI::Color color, UI::Control::State state);
        
        void setImage(UI::Image image, UI::Control::State state);
        
        void setBackgroundImage(UI::Image image, UI::Control::State state);

#endif  //__APPLE__
        
    };
}

#endif  //__MITSOKO__IOS_UTIL__UI__BUTTON__
