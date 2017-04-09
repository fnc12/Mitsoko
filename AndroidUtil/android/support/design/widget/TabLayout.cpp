//
//  TabLayout.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TabLayout.hpp"

#ifdef __ANDROID__

const std::string android::support::design::widget::TabLayout::signature = "android/support/design/widget/TabLayout";

const std::string android::support::design::widget::TabLayout::Tab::signature = "android/support/design/widget/TabLayout$Tab";

auto android::support::design::widget::TabLayout::Tab::setText(const std::string &text) -> Tab& {
    auto s=java::lang::String::create(text);
    return this->setText(s);
}

auto android::support::design::widget::TabLayout::Tab::setText(const java::lang::CharSequence &text) -> Tab& {
    this->sendMessage<Tab>("setText",text);
    return *this;
}

int android::support::design::widget::TabLayout::GRAVITY_FILL(){
    if(java::lang::Class cls=java::lang::Class::find<TabLayout>()){
        return cls.getStaticField<int>("GRAVITY_FILL");
    }else{
        return -1;
    }
}

void android::support::design::widget::TabLayout::setTabGravity(int gravity){
    this->sendMessage<void>("setTabGravity",gravity);
}

auto android::support::design::widget::TabLayout::newTab()->Tab{
    return this->sendMessage<Tab>("newTab");
}

void android::support::design::widget::TabLayout::addTab(const Tab &tab){
    this->sendMessage<void>("addTab",tab);
}

auto android::support::design::widget::TabLayout::getTabAt(int index)->Tab{
    return this->sendMessage<Tab>("getTabAt",index);
}

#endif  //__ANDROID__
