//
//  SegmentedControl.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "SegmentedControl.hpp"

#ifdef __APPLE__

const std::string UI::SegmentedControl::className="UISegmentedControl";

void UI::SegmentedControl::setTintColor(const UI::Color &newValue){
    this->sendMessage<void>("setTintColor:", newValue.handle);
}

UI::Color UI::SegmentedControl::tintColor(){
    return this->sendMessage<Handle>("tintColor");
}

void UI::SegmentedControl::setSelectedSegmentIndex(int newValue){
    this->sendMessage<void>("setSelectedSegmentIndex:", NSInteger(newValue));
}

int UI::SegmentedControl::selectedSegmentIndex(){
    return int(this->sendMessage<NSInteger>("selectedSegmentIndex"));
}

void UI::SegmentedControl::setTitle(const std::string &title,int segment){
    auto t=CF::String::create(title);
    this->setTitle(t, segment);
}

void UI::SegmentedControl::setTitle(const CF::String &title,int segment){
    this->sendMessage<void>("setTitle:forSegmentAtIndex:", title.handle, NSUInteger(segment));
}

std::string UI::SegmentedControl::titleForSegmentAtIndex(int segment){
    return this->sendMessage<NSString*>("titleForSegmentAtIndex:", NSUInteger(segment)).UTF8String;
}

#endif  //__APPLE__
