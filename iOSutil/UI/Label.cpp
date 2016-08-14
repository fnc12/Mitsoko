//
//  Label.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Label.hpp"

#ifdef __APPLE__

const std::string UI::Label::className="UILabel";

void UI::Label::setText(const std::string &newValue){
    auto str=CF::String::create(newValue);
    this->sendMessage<void>("setText:", str.handle);
}

void UI::Label::setTextColor(const UI::Color &newValue){
    this->sendMessage<void>("setTextColor:", newValue.handle);
}

UI::Color UI::Label::textColor(){
    return this->sendMessage<Handle>("textColor");
}

#endif  //__APPLE__
