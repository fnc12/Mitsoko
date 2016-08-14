//
//  TextView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TextView.hpp"

#ifdef __APPLE__

void UI::TextView::setText(const CF::String &newValue){
    this->sendMessage<void>("setText:", newValue.handle);
}

void UI::TextView::setText(const std::string &newValue){
    auto t=CF::String::create(newValue);
    this->setText(t);
}

std::string UI::TextView::text(){
    return this->sendMessage<NSString*>("text").UTF8String;
}

#endif  //__APPLE__
