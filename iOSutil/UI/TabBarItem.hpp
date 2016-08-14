
#ifndef __VIPER__IOS_UTIL__UI__TAB_BAT_ITEM__
#define __VIPER__IOS_UTIL__UI__TAB_BAT_ITEM__

#include "BarItem.hpp"
#include "Image.hpp"

namespace UI {
    struct TabBarItem:public UI::BarItem{
        using BarItem::BarItem;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UITabBarItem");
        
        void setSelectedImage(const UI::Image &newValue);
        
        UI::Image selectedImage();
#endif
    };
}

#endif
