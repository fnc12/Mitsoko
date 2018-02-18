
#ifndef __MITSOKO__IOS_UTIL__UI__TAB_BAR__
#define __MITSOKO__IOS_UTIL__UI__TAB_BAR__

#include "Mitsoko/iOSutil/UI/View.hpp"
#include "Mitsoko/iOSutil/UI/TabBarItem.hpp"
#include "Mitsoko/iOSutil/NS/Array.hpp"

namespace UI {
    
    struct TabBar : public UI::View {
        using View::View;
#ifdef __APPLE__
        
        static const std::string className;
        
        void setSelectedItem(UI::TabBarItem item);
        
        NS::Array items();
        
#endif  //  __APPLE__
    };
}

#endif /* __MITSOKO__IOS_UTIL__UI__TAB_BAR__ */
