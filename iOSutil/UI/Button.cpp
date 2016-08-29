//
//  Button.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Button.hpp"

#ifdef __APPLE__

const std::string UI::Button::className="UIButton";

void UI::Button::setTitle(const std::string &title,UI::Control::State state){
    auto str=CF::String::create(title);
    this->sendMessage<void>("setTitle:forState:", str.handle,UIControlState(state));
}

#endif  //__APPLE__
