//
//  AlertView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "AlertView.hpp"

#ifdef __APPLE__

const std::string UI::AlertView::className="UIAlertView";

UI::AlertView::DelegateEventHandler::DelegateEventHandlersMap UI::AlertView::DelegateEventHandler::delegateEventHandlers;

void UI::AlertView::setDidDismissWithButtonIndex(DidDismissWithButtonIndex f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIAlertViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).didDismissWithButtonIndex=f;
}

void UI::AlertView::setWillDismissWithButtonIndex(WillDismissWithButtonIndex f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIAlertViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).willDismissWithButtonIndex=f;
}

void UI::AlertView::setClickedButtonAtIndex(ClickedButtonAtIndex f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIAlertViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).clickedButtonAtIndex=f;
}

void UI::AlertView::setMessage(std::experimental::optional<std::string> newValue){
    auto str=CF::String::create(newValue);
    this->setMessage(str);
}

void UI::AlertView::setMessage(const CF::String &newValue){
    this->sendMessage<void>("setMessage:", newValue.handle);
}

std::string UI::AlertView::message(){
    NS::String res=this->sendMessage<Handle>("message");
    return res.UTF8String();
}

int UI::AlertView::addButtonWithTitle(const std::string &title){
    auto t=CF::String::create(title);
    return this->addButtonWithTitle(t);
}

int UI::AlertView::addButtonWithTitle(const CF::String &title){
    return int(this->sendMessage<NSInteger>("addButtonWithTitle:", title.handle));
}

void UI::AlertView::setCancelButtonIndex(int newValue){
    this->sendMessage<void>("setCancelButtonIndex:", NSInteger(newValue));
}

int UI::AlertView::cancelButtonIndex(){
    return int(this->sendMessage<NSInteger>("cancelButtonIndex"));
}

void UI::AlertView::setAlertViewStyle(Style newValue){
    this->sendMessage<void>("setAlertViewStyle:", UIAlertViewStyle(newValue));
}

auto UI::AlertView::alertViewStyle()->Style{
    return Style(this->sendMessage<UIAlertViewStyle>("alertViewStyle"));
}

void UI::AlertView::setTitle(const std::string &newValue){
    auto v=CF::String::create(newValue);
    this->setTitle(v);
}

void UI::AlertView::setTitle(const CF::String &newValue){
    this->sendMessage<void>("setTitle:", newValue.handle);
}

std::string UI::AlertView::title(){
    NS::String res=this->sendMessage<Handle>("title");
    return res.UTF8String();
}

void UI::AlertView::show(){
    this->sendMessage<void>("show");
}

UI::TextField UI::AlertView::textFieldAtIndex(int index){
    return this->sendMessage<Handle>("textFieldAtIndex:", NSInteger(index));
}

UI::AlertView UI::AlertView::create(std::experimental::optional<std::string> title,
                                    std::experimental::optional<std::string> message,
                                    std::experimental::optional<std::string> cancelButtonTitle,
                                    std::initializer_list<std::string> otherButtonTitles)
{
    return std::move(create(CF::String::create(title),
                            CF::String::create(message),
                            CF::String::create(cancelButtonTitle),
                            std::move(otherButtonTitles)));
}

UI::AlertView UI::AlertView::create(const CF::String &title,
                                    const CF::String &message,
                                    const CF::String &cancelButtonTitle,
                                    std::initializer_list<std::string> otherButtonTitles)
{
    auto cls=NS::getClass(className);
    if(cls){
        auto res=NS::Object::create<AlertView>();
        res.setTitle(title);
        res.setMessage(message);
        if(cancelButtonTitle){
            res.setCancelButtonIndex(res.addButtonWithTitle(cancelButtonTitle));
        }
        for(const auto &t:otherButtonTitles){
            auto s=CF::String::create(t);
            res.addButtonWithTitle(s);
        }
        return std::move(res);
    }else{
        return {};
    }
}

auto UI::AlertView::DelegateEventHandler::getOrCreate(const void *aw)->DelegateEventHandler&{
    auto it=delegateEventHandlers.find(aw);
    if(it != delegateEventHandlers.end()){
        return it->second;
    }else{
        return delegateEventHandlers.insert({aw,{}}).first->second;
    }
}

auto UI::AlertView::DelegateEventHandler::get(const void *aw)->DelegateEventHandler*{
    auto it=delegateEventHandlers.find(aw);
    if(it != delegateEventHandlers.end()){
        return &it->second;
    }else{
        return nullptr;
    }
}

void UI::AlertView::DelegateEventHandler::remove(const void *aw){
    auto it=delegateEventHandlers.find(aw);
    if(it != delegateEventHandlers.end()){
        delegateEventHandlers.erase(it);
    }
}

void UI::AlertView::DelegateEventHandler::alertViewDidDismissWithButtonIndex(const void *aw,int buttonIndex){
    if(auto e=get(aw)){
        if(e->didDismissWithButtonIndex){
            e->didDismissWithButtonIndex(aw,buttonIndex);
        }
        
        //  expliclty specifying class name cause there is int remove(const char *) function
        //  in C standard library..
        DelegateEventHandler::remove(aw);
    }
}

void UI::AlertView::DelegateEventHandler::alertViewWillDismissWithButtonIndex(const void *aw,int buttonIndex){
    if(auto e=get(aw)){
        if(e->willDismissWithButtonIndex){
            e->willDismissWithButtonIndex(aw,buttonIndex);
        }
    }
}

void UI::AlertView::DelegateEventHandler::alertViewClickedButtonAtIndex(const void *aw,int buttonIndex){
    if(auto e=get(aw)){
        if(e->clickedButtonAtIndex){
            e->clickedButtonAtIndex(aw,buttonIndex);
        }
    }
}

#endif  //__APPLE__
