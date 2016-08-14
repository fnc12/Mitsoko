//
//  ActionSheet.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ActionSheet.hpp"

#ifdef __APPLE__

const std::string UI::ActionSheet::className="UIActionSheet";

UI::ActionSheet::DelegateEventHandler::DelegateEventHandlersMap UI::ActionSheet::DelegateEventHandler::delegateEventHandlers;

UI::ActionSheet UI::ActionSheet::create(){
    return NS::Object::create<UI::ActionSheet>();
}

void UI::ActionSheet::setDidDismissWithButtonIndex(DidDismissWithButtonIndex f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIActionSheetDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).didDismissWithButtonIndex=f;
}

void UI::ActionSheet::setWillDismissWithButtonIndex(WillDismissWithButtonIndex f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIActionSheetDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).willDismissWithButtonIndex=f;
}

void UI::ActionSheet::setClickedButtonAtIndex(ClickedButtonAtIndex f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIActionSheetDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).clickedButtonAtIndex=f;
}

void UI::ActionSheet::showInView(const UI::View &view){
    this->sendMessage<void>("showInView:", view.handle);
}

void UI::ActionSheet::setDestructiveButtonIndex(int newValue){
    this->sendMessage<void>("setDestructiveButtonIndex:", NSInteger(newValue));
}

int UI::ActionSheet::destructiveButtonIndex(){
    return int(this->sendMessage<NSInteger>("destructiveButtonIndex"));
}

void UI::ActionSheet::setCancelButtonIndex(int newValue){
    this->sendMessage<void>("setCancelButtonIndex:", NSInteger(newValue));
}

int UI::ActionSheet::cancelButtonIndex(){
    return int(this->sendMessage<NSInteger>("cancelButtonIndex"));
}

int UI::ActionSheet::numberOfButtons(){
    return int(this->sendMessage<NSInteger>("numberOfButtons"));
}

NS::String UI::ActionSheet::buttonTitleAtIndex(int index){
    return this->sendMessage<Handle>("buttonTitleAtIndex:", NSInteger(index));
}

int UI::ActionSheet::addButtonWithTitle(const std::string &t){
    auto str=CF::String::create(t);
    return this->addButtonWithTitle(str);
}

int UI::ActionSheet::addButtonWithTitle(const CF::String &t){
    return int(this->sendMessage<NSInteger>("addButtonWithTitle:", t.handle));
}

void UI::ActionSheet::setTitle(const std::string &newValue){
    auto str=CF::String::create(newValue);
    this->setTitle(str);
}

void UI::ActionSheet::setTitle(const CF::String &newValue){
    this->sendMessage<void>("setTitle:", newValue.handle);
}

std::string UI::ActionSheet::title(){
    NS::String res=this->sendMessage<Handle>("title");
    return res.UTF8String();
}

auto UI::ActionSheet::DelegateEventHandler::getOrCreate(const void *as)->DelegateEventHandler&{
    auto it=delegateEventHandlers.find(as);
    if(it != delegateEventHandlers.end()){
        return it->second;
    }else{
        return delegateEventHandlers.insert({as,{}}).first->second;
    }
}

auto UI::ActionSheet::DelegateEventHandler::get(const void *as)->DelegateEventHandler*{
    auto it=delegateEventHandlers.find(as);
    if(it != delegateEventHandlers.end()){
        return &it->second;
    }else{
        return nullptr;
    }
}

void UI::ActionSheet::DelegateEventHandler::remove(const void *as){
    auto it=delegateEventHandlers.find(as);
    if(it != delegateEventHandlers.end()){
        delegateEventHandlers.erase(it);
    }
}

void UI::ActionSheet::DelegateEventHandler::actionSheetDidDismissWithButtonIndex(const void *as,int buttonIndex){
    if(auto e=get(as)){
        if(e->didDismissWithButtonIndex){
            e->didDismissWithButtonIndex(as,buttonIndex);
        }
        
        //  expliclty specifying class name cause there is int remove(const char *) function
        //  in C standard library..
        DelegateEventHandler::remove(as);
    }
}

void UI::ActionSheet::DelegateEventHandler::actionSheetWillDismissWithButtonIndex(const void *as,int buttonIndex){
    if(auto e=get(as)){
        if(e->willDismissWithButtonIndex){
            e->willDismissWithButtonIndex(as,buttonIndex);
        }
    }
}

void UI::ActionSheet::DelegateEventHandler::actionSheetClickedButtonAtIndex(const void *as,int buttonIndex){
    if(auto e=get(as)){
        if(e->clickedButtonAtIndex){
            e->clickedButtonAtIndex(as,buttonIndex);
        }
    }
}

#endif  //__APPLE__
