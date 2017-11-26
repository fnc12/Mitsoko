//
//  Control.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Control.hpp"

#ifdef __APPLE__

static auto actionSelectorName = "actionDidHappen:";

using Mitsoko::Disposable;

const std::string UI::Control::className = "UIControl";

void UI::Control::setEnabled(bool newValue){
    this->sendMessage<void>("setEnabled:",newValue);
}

bool UI::Control::enabled(){
    return this->sendMessage<bool>("isEnabled");
}

void UI::Control::setSelected(bool value) {
    this->sendMessage<void>("setSelected:", BOOL(value));
}

bool UI::Control::isSelected() {
    return this->sendMessage<BOOL>("isSelected");
}

void UI::Control::setOnValueChanged(Callback cb, Mitsoko::Disposable &target){
    if(cb){
        EventHandler<Events::ValueChanged>::add(this->handle, cb);
        auto cls = NS::getClass("UIControlValueChangedEventHandler");
        auto sharedEventHandler = NS::Object::sendMessage<Handle>(cls, "shared");
        auto sel = sel_getUid(actionSelectorName);
        this->sendMessage<void>("addTarget:action:forControlEvents:", sharedEventHandler, sel, UIControlEventValueChanged);
    }else{
        EventHandler<Events::ValueChanged>::remove(this->handle);
    }
}

void UI::Control::setOnTouchUpInside(Callback cb, Disposable *target){
    if(cb && target){
        EventHandler<Events::TouchUpInside>::add(this->handle, cb);
        auto cls = NS::getClass("UIControlTouchUpInsideEventHandler");
        auto sharedEventHandler = NS::Object::sendMessage<Handle>(cls, "shared");
        auto sel = sel_getUid(actionSelectorName);
        this->sendMessage<void>("addTarget:action:forControlEvents:", sharedEventHandler, sel, UIControlEventTouchUpInside);
    }else{
        EventHandler<Events::TouchUpInside>::remove(this->handle);
    }
}

void UI::Control::setOnEditingChanged(Callback cb, Mitsoko::Disposable &target) {
    if(cb){
        EventHandler<Events::EditingChanged>::add(this->handle, cb);
        auto cls = NS::getClass("UIControlEditingChangedEventHandler");
        auto sharedEventHandler = NS::Object::sendMessage<Handle>(cls, "shared");
        auto sel = sel_getUid(actionSelectorName);
        this->sendMessage<void>("addTarget:action:forControlEvents:", sharedEventHandler, sel, UIControlEventEditingChanged);
    }else{
        EventHandler<Events::EditingChanged>::remove(this->handle);
    }
}

#endif  //__APPLE__
