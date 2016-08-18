//
//  TextView.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TextView.hpp"

#ifdef __ANDROID__

//const std::string android::widget::TextView::signature="android/widget/TextView";

void android::widget::TextView::setInputType(int type){
    this->sendMessage<void>("setInputType",type);
}

void android::widget::TextView::setTextColor(int color){
    this->sendMessage<void>("setTextColor",color);
}

void android::widget::TextView::setText(const std::string &value){
    auto str=java::lang::String::create(value);
    this->setText(str);
}

void android::widget::TextView::setText(const java::lang::String &str){
    this->sendMessage<void>("setText",(java::lang::CharSequence)str);
}

#endif  //__ANDROID__
