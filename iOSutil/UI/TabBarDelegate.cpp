//
//  TabBarDelegate.cpp
//  GoZebra
//
//  Created by John Zakharov on 18.02.2018.
//  Copyright © 2018 Outlaw Studio. All rights reserved.
//

#include "TabBarDelegate.hpp"

#ifdef __APPLE__

const std::string UI::TabBarDelegate::className = "UITabBarDelegate";

void UI::TabBarDelegate::tabBarDidSelectItem(UI::TabBar tabBar, UI::TabBarItem item) {
    this->sendMessage<void>("tabBar:didSelectItem:", tabBar.handle, item.handle);
}

void UI::TabBarDelegate::tabBarWillBeginCustomizingItems(UI::TabBar tabBar, NS::Array items) {
    this->sendMessage<void>("tabBar:willBeginCustomizingItems:", tabBar.handle, items.handle);
}

void UI::TabBarDelegate::tabBarDidBeginCustomizingItems(UI::TabBar tabBar, NS::Array items) {
    this->sendMessage<void>("tabBar:didBeginCustomizingItems:", tabBar.handle, items.handle);
}

void UI::TabBarDelegate::tabBarWillEndCustomizingItems(UI::TabBar tabBar, NS::Array items, bool changed) {
    this->sendMessage<void>("tabBar:willEndCustomizingItems:changed:", tabBar.handle, items.handle, changed);
}

void UI::TabBarDelegate::tabBarDidEndCustomizingItems(UI::TabBar tabBar, NS::Array items, bool changed) {
    this->sendMessage<void>("tabBar:didEndCustomizingItems:changed:", tabBar.handle, items.handle, changed);
}

#endif  //  __APPLE__
