
#ifndef __VIPER__IOS_UTIL__UI__PAGE_CONTROL__
#define __VIPER__IOS_UTIL__UI__PAGE_CONTROL__

#include "Control.hpp"

namespace UI {
    struct PageControl:public UI::Control{
        using Control::Control;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UIPageControl");
        
        void setNumberOfPages(int newValue);
        
        int numberOfPages();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__PAGE_CONTROL__
