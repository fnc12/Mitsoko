//
//  NavigationItem.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "NavigationItem.hpp"

#ifdef __APPLE__

const std::string UI::NavigationItem::className="UINavigationItem";

void UI::NavigationItem::setHidesBackButton(bool newValue){
    this->sendMessage<void>("setHidesBackButton:", BOOL(newValue));
}

bool UI::NavigationItem::hidesBackButton(){
    return this->sendMessage<BOOL>("hidesBackButton");
}

void UI::NavigationItem::setTitle(const std::string &newValue){
    auto str=CF::String::create(newValue);
    this->sendMessage<void>("setTitle:", str.handle);
}

void UI::NavigationItem::setBackBarButtonItem(const UI::BarButtonItem &newValue){
    this->sendMessage<void>("setBackBarButtonItem:", newValue.handle);
}

UI::BarButtonItem UI::NavigationItem::backBarButtonItem(){
    return this->sendMessage<Handle>("backBarButtonItem");
}

void UI::NavigationItem::setRightBarButtonItem(const UI::BarButtonItem &item){
    this->sendMessage<void>("setRightBarButtonItem:",item.handle);
}

UI::BarButtonItem UI::NavigationItem::rightBarButtonItem(){
    return this->sendMessage<Handle>("rightBarButtonItem");
}

#endif  //__APPLE__
