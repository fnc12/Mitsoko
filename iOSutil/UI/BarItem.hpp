
#ifndef __VIPER__IOS_UTIL__UI__BAR_ITEM__
#define __VIPER__IOS_UTIL__UI__BAR_ITEM__

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/iOSutil/NS/String.hpp"
#include "Image.hpp"
#include "Viper/iOSutil/CF/String.hpp"

namespace UI {
    
    struct BarItem:public NS::Object{
        
        using Object::Object;

#ifdef __APPLE__
        
        static const std::string className;
        
        void setTag(int newValue);
        
        int tag();
        
        void setImage(const UI::Image &newValue);
        
        UI::Image image();
        
        void setTitle(const std::string &newValue);
        
        void setTitle(const CF::String &newValue);
        
        std::string title();
        
        void setEnabled(bool newValue);
        
#endif  //__APPLE__
        
    };
}

#endif  //__VIPER__IOS_UTIL__UI__BAR_ITEM__
