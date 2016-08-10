//
//  NavigationBar.cpp
//  Groozim
//
//  Created by John Zakharov on 10.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "NavigationBar.hpp"

#ifdef __APPLE__

const std::string UI::NavigationBar::className="UINavigationBar";

UI::NavigationBar UI::NavigationBar::appearance(){
    auto cls=NS::getClass(className);
    return sendMessage<Handle>(cls, "appearance");
}

void UI::NavigationBar::setBarTintColor(const UI::Color &newValue){
    this->sendMessage<void>("setBarTintColor:", newValue.handle);
}

UI::Color UI::NavigationBar::barTintColor(){
    return this->sendMessage<Handle>("barTintColor");
}

void UI::NavigationBar::setTintColor(const UI::Color &newValue){
    this->sendMessage<void>("setTintColor:", newValue.handle);
}

UI::Color UI::NavigationBar::tintColor(){
    return this->sendMessage<Handle>("tintColor");
}

#endif  //__APPLE__
