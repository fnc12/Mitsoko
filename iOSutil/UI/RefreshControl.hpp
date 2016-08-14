
#ifndef __VIPER__IOS_UTIL__UI__REFRESH_CONTROL__
#define __VIPER__IOS_UTIL__UI__REFRESH_CONTROL__

#include "Control.hpp"

namespace UI {
    struct RefreshControl:public UI::Control{
        using Control::Control;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        void endRefreshing();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__REFRESH_CONTROL__
