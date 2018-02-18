
#include "TabBar.hpp"

#ifdef __APPLE__

const std::string UI::TabBar::className = "UITabBar";

void UI::TabBar::setSelectedItem(UI::TabBarItem item) {
    this->sendMessage<void>("setSelectedItem:", item.handle);
}

NS::Array UI::TabBar::items() {
    return this->sendMessage<Handle>("items");
}

#endif  //  __APPLE__
