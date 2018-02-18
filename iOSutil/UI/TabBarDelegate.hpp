
#ifndef __MITSOKO__IOS_UTIL__UI__TAB_BAR_DELEGATE__
#define __MITSOKO__IOS_UTIL__UI__TAB_BAR_DELEGATE__

#include "Mitsoko/iOSutil/NS/Object.hpp"
#include "Mitsoko/iOSutil/UI/TabBarItem.hpp"
#include "Mitsoko/iOSutil/UI/TabBar.hpp"
#include "Mitsoko/iOSutil/NS/Array.hpp"
namespace UI {
    
    struct TabBarDelegate : public NS::Object {
        using Object::Object;
#ifdef __APPLE__
        
        static const std::string className;
        
        void tabBarDidSelectItem(UI::TabBar tabBar, UI::TabBarItem item);
        
        void tabBarWillBeginCustomizingItems(UI::TabBar tabBar, NS::Array items);
        
        void tabBarDidBeginCustomizingItems(UI::TabBar tabBar, NS::Array items);
        
        void tabBarWillEndCustomizingItems(UI::TabBar tabBar, NS::Array items, bool changed);
        
        void tabBarDidEndCustomizingItems(UI::TabBar tabBar, NS::Array items, bool changed);
        
#endif  //  __APPLE__
    };
}

#endif /* __MITSOKO__IOS_UTIL__UI__TAB_BAR_DELEGATE__ */
