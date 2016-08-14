//
//  TextField.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TextField.hpp"

#ifdef __APPLE__

UI::TextField::TextField():
UI::Control(),
UI::TextInput(){}

UI::TextField::TextField(Handle handle):
UI::Control(handle),
UI::TextInput(handle){}

void UI::TextField::setText(const std::string &newValue){
    auto s=CF::String::create(newValue);
    this->setText(s);
}

void UI::TextField::setText(const CF::String &newValue){
    this->Super::sendMessage<void>("setText:", newValue.handle);
}

std::string UI::TextField::text(){
    auto t=this->Super::sendMessage<NSString*>("text");
    if(t){
        return t.UTF8String;
    }else{
        return {};
    }
}

#endif  //__APPLE__
