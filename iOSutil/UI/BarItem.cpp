//
//  BarItem.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "BarItem.hpp"

#ifdef __APPLE__

const std::string UI::BarItem::className="UIBarItem";

void UI::BarItem::setTag(int newValue){
    this->sendMessage<void>("setTag:", NSInteger(newValue));
}

int UI::BarItem::tag(){
    return int(this->sendMessage<NSInteger>("tag"));
}

void UI::BarItem::setImage(const UI::Image &newValue){
    this->sendMessage<void>("setImage:", newValue.handle);
}

UI::Image UI::BarItem::image(){
    return this->sendMessage<Handle>("image");
}

void UI::BarItem::setTitle(const std::string &newValue){
    auto s=CF::String::create(newValue);
    this->setTitle(s);
}

void UI::BarItem::setTitle(const CF::String &newValue){
    this->sendMessage<void>("setTitle:", newValue.handle);
}

std::string UI::BarItem::title(){
    NS::String res=this->sendMessage<Handle>("title");
    return res.UTF8String();
}

void UI::BarItem::setEnabled(bool newValue){
    this->sendMessage<void>("setEnabled:", newValue);
}

#endif  //__APPLE__
