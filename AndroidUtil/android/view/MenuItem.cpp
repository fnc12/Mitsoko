//
//  MenuItem.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "MenuItem.hpp"

#ifdef __ANDROID__

const std::string android::view::MenuItem::signature = "android/view/MenuItem";

auto android::view::MenuItem::setTitle(const std::string &title)->MenuItem&{
    auto str=java::lang::String::create(title);
    return this->setTitle(str);
}

auto android::view::MenuItem::setTitle(const java::lang::CharSequence &title)->MenuItem&{
    this->sendMessage<MenuItem>("setTitle",title);
    return *this;
}

std::string android::view::MenuItem::getTitle(){
    return this->sendMessage<java::lang::CharSequence>("getTitle").toString().c_str();
}

#endif  //__ANDROID__
