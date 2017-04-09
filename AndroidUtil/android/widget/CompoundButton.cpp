//
//  CompoundButton.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "CompoundButton.hpp"

#ifdef __ANDROID__

const std::string android::widget::CompoundButton::signature = "android/widget/CompoundButton";
 
const std::string android::widget::CompoundButton::OnCheckedChangeListener::signature = "android/widget/CompoundButton$OnCheckedChangeListener";

android::widget::CompoundButton::OnCheckedMap android::widget::CompoundButton::onCheckedMap;

void android::widget::CompoundButton::onCheckedChanged(int id,jobject sender,bool checked){
    auto it=onCheckedMap.find(id);
    if(it != onCheckedMap.end()){
        it->second(sender,checked);
    }
}

void android::widget::CompoundButton::setChecked(bool newValue){
    this->sendMessage<void>("setChecked",newValue);
}

bool android::widget::CompoundButton::isChecked(){
    return this->sendMessage<bool>("isChecked");
}

void android::widget::CompoundButton::setOnCheckedChangeListener(OnCheckedChangeCallback cb){
    CompoundButton::OnCheckedChangeListener l;
    if(cb){
        auto classSignature="kz/outlawstudio/viper/EventHandlers$CompoundButtonOnCheckedChangeListener";
        auto callbackObject=java::lang::Object::create(classSignature);
        auto callbackId=callbackObject.getField<int>("mId");
        onCheckedMap.insert({callbackId,cb});
        l=(OnCheckedChangeListener)callbackObject;
    }
    this->sendMessage<void>("setOnCheckedChangeListener",l);
}

#endif  //__ANDROID__
