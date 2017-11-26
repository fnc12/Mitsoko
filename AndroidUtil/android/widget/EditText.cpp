//
//  EditText.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "EditText.hpp"

#ifdef __ANDROID__

const std::string android::widget::EditText::signature = "android/widget/EditText";

auto android::widget::EditText::create(const content::Context &context)->EditText{
    return std::move(java::lang::Object::create<EditText>(context));
}

android::text::Editable android::widget::EditText::getText(){
    return this->sendMessage<android::text::Editable>("getText");
}

void android::widget::EditText::addTextChangedListener(const android::text::TextWatcher &watcher){
    this->sendMessage<void>("addTextChangedListener", watcher);
}

void android::widget::EditText::addTextChangedListener(std::function<void(java::lang::CharSequence, int, int, int)> beforeTextChanged,
                                                       std::function<void(java::lang::CharSequence, int, int, int)> onTextChanged,
                                                       std::function<void(android::text::Editable)> afterTextChanged,
                                                       Mitsoko::Disposable &disposable)
{
    auto classSignature = "kz/outlawstudio/viper/EventHandlers$TextViewTextChangedListener";
    auto textWatcherObject = java::lang::Object::create(classSignature);
    auto textWatcherId = textWatcherObject.getField<int>("mId");
    if(onTextChanged){
        TextWatcherEventHandler::onTextChangedMap.insert({textWatcherId, onTextChanged});
    }
    if(beforeTextChanged){
        TextWatcherEventHandler::beforeTextChangedMap.insert({textWatcherId, beforeTextChanged});
    }
    if(afterTextChanged){
        TextWatcherEventHandler::afterTextChangedMap.insert({textWatcherId, afterTextChanged});
    }
    TextWatcherEventHandler::disposablesMap[disposable.id].push_back(textWatcherId);
    this->addTextChangedListener((android::text::TextWatcher)textWatcherObject);
}

#endif  //__ANDROID__
