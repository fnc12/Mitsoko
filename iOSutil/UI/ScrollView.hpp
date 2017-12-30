
#ifndef __VIPER__IOS_UTIL__UI__SCROLL_VIEW__
#define __VIPER__IOS_UTIL__UI__SCROLL_VIEW__

#include "View.hpp"
#include "Mitsoko/iOSutil/CG/Size.hpp"
#include "Mitsoko/Util.hpp"

namespace UI {
    struct ScrollView:public UI::View{
        using View::View;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        void setContentSize(const CG::Size &newValue);
        
        CG::Size contentSize();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__SCROLL_VIEW__
