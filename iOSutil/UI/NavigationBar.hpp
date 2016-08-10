
#ifndef __VIPER__IOS_UTIL__UI__NAVIGATION_BAR__
#define __VIPER__IOS_UTIL__UI__NAVIGATION_BAR__

#include "View.hpp"
#include "Color.hpp"

namespace UI {
    struct NavigationBar:public UI::View{
        using View::View;
#ifdef __APPLE__
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UINavigationBar");
        
        static UI::NavigationBar appearance();
        
        void setBarTintColor(const UI::Color &newValue);
        
        UI::Color barTintColor();
        
        void setTintColor(const UI::Color &newValue);
        
        UI::Color tintColor();
#endif
    };
}

#endif
