//
//  ActionBar.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ActionBar.hpp"

#ifdef __ANDROID__

//const std::string android::support::v7::app::ActionBar::signature="android/support/v7/app/ActionBar";

java::lang::CharSequence android::support::v7::app::ActionBar::getTitle(){
    return this->sendMessage<java::lang::CharSequence>("getTitle");
}

void android::support::v7::app::ActionBar::setTitle(const std::string &title){
    auto t=java::lang::String::create(title);
    this->setTitle(t);
}

void android::support::v7::app::ActionBar::setTitle(const java::lang::CharSequence &title){
    this->sendMessage<void>("setTitle",title);
}

void android::support::v7::app::ActionBar::hide(){
    this->sendMessage<void>("hide");
}

#endif  //__ANDROID__
