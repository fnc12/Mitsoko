//
//  Control.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Control.hpp"

#ifdef __APPLE__

const std::string UI::Control::className="UIControl";

UI::Control::ValueChangedEventHandler::Callbacks UI::Control::ValueChangedEventHandler::callbacks;

void UI::Control::setEnabled(bool newValue){
    this->sendMessage<void>("setEnabled:",newValue);
}

bool UI::Control::enabled(){
    return this->sendMessage<bool>("isEnabled");
}

void UI::Control::setOnValueChanged(Callback cb){
    if(cb){
        ValueChangedEventHandler::add(this->handle, cb);
        auto cls=NS::getClass("UIControlValueChangedEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(cls,"shared");
        auto sel=sel_getUid("actionDidHappen:");
        this->sendMessage<void>("addTarget:action:forControlEvents:", sharedEventHandler, sel, UIControlEventValueChanged);
    }else{
        ValueChangedEventHandler::remove(this->handle);
    }
}

void UI::Control::ValueChangedEventHandler::add(Handle handle,Callback cb){
    auto it=ValueChangedEventHandler::callbacks.find(handle);
    if(it != ValueChangedEventHandler::callbacks.end()){
        it->second=cb;
    }else{
        ValueChangedEventHandler::callbacks.insert({handle,cb});
    }
}

auto UI::Control::ValueChangedEventHandler::get(Handle handle)->Callback{
    auto it=ValueChangedEventHandler::callbacks.find(handle);
    if(it != ValueChangedEventHandler::callbacks.end()){
        return it->second;
    }else{
        return {};
    }
}

void UI::Control::ValueChangedEventHandler::remove(Handle handle){
    auto it=ValueChangedEventHandler::callbacks.find(handle);
    if(it != ValueChangedEventHandler::callbacks.end()){
        ValueChangedEventHandler::callbacks.erase(it);
    }else{
        //                    ValueChangedEventHandler::callbacks().insert({handle,cb});
    }
}

void UI::Control::ValueChangedEventHandler::actionDidHappen(Handle sender){
    if(auto cb=get(sender)){
        cb(sender);
    }
}

#endif  //__APPLE__
