//
//  Button.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Button.hpp"

#ifdef __APPLE__

const std::string UI::Button::className = "UIButton";

void UI::Button::setTitle(const std::string &title,UI::Control::State state){
    auto str = CF::String::create(title);
    this->sendMessage<void>("setTitle:forState:", str.handle, UIControlState(state));
}

void UI::Button::setTitleColor(UI::Color color, UI::Control::State state) {
    this->sendMessage<void>("setTitleColor:forState:", color.handle, UIControlState(state));
}

void UI::Button::setImage(UI::Image image, UI::Control::State state) {
    this->sendMessage<void>("setImage:forState:", image.handle, UIControlState(state));
}

void UI::Button::setBackgroundImage(UI::Image image, UI::Control::State state) {
    this->sendMessage<void>("setBackgroundImage:forState:", image.handle, UIControlState(state));
}

#endif  //__APPLE__
