//
//  TextView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TextView.hpp"

#ifdef __APPLE__

const std::string UI::TextView::className="UITextView";

UI::TextView::DelegateEventHandler::DelegateEventHandlersMap UI::TextView::DelegateEventHandler::delegateEventHandlers;

UI::TextView::DelegateEventHandler::DisposablesMap UI::TextView::DelegateEventHandler::disposablesMap;

UI::TextView::DelegateEventHandler::Observer UI::TextView::DelegateEventHandler::observer;

void UI::TextView::setText(const CF::String &newValue){
    this->sendMessage<void>("setText:", newValue.handle);
}

void UI::TextView::setText(const std::string &newValue){
    auto t=CF::String::create(newValue);
    this->setText(t);
}

std::string UI::TextView::text(){
    return this->sendMessage<NSString*>("text").UTF8String;
}

auto UI::TextView::DelegateEventHandler::getOrCreate(const void *sender)->DelegateEventHandler&{
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        return it->second;
    }else{
        return delegateEventHandlers.insert({sender,{}}).first->second;
    }
}

auto UI::TextView::DelegateEventHandler::get(const void *tv)->DelegateEventHandler*{
    auto it=delegateEventHandlers.find(tv);
    if(it != delegateEventHandlers.end()){
        return &it->second;
    }else{
        return nullptr;
    }
}

void UI::TextView::DelegateEventHandler::remove(const void *tv){
    auto it=delegateEventHandlers.find(tv);
    if(it != delegateEventHandlers.end()){
        delegateEventHandlers.erase(it);
    }
}

bool UI::TextView::DelegateEventHandler::textViewShouldBeginEditing(Handle sender){
    https://developer.apple.com/library/ios/documentation/UIKit/Reference/UITextViewDelegate_Protocol/#//apple_ref/occ/intfm/UITextViewDelegate/textViewShouldBeginEditing:
    const auto defaultReturnValue=true;
    
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.shouldBeginEditing){
            return it->second.shouldBeginEditing();
        }else{
            return defaultReturnValue;
        }
    }else{
        return defaultReturnValue;
    }
}

void UI::TextView::DelegateEventHandler::textViewDidBeginEditing(Handle sender){
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.didBeginEditing){
            it->second.didBeginEditing();
        }
    }
}

bool UI::TextView::DelegateEventHandler::textViewShouldEndEditing(Handle sender){
    const auto defaultReturnValue=true;
    
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.shouldEndEditing){
            return it->second.shouldEndEditing();
        }else{
            return defaultReturnValue;
        }
    }else{
        return defaultReturnValue;
    }
}

void UI::TextView::DelegateEventHandler::textViewDidEndEditing(Handle sender){
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.didEndEditing){
            it->second.didEndEditing();
        }
    }
}

bool UI::TextView::DelegateEventHandler::textViewShouldChangeTextInRange(Handle sender, NSRange range, Handle text){
    const auto defaultReturnValue=true;
    
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.shouldChangeTextInRange){
            return it->second.shouldChangeTextInRange(range,text);
        }else{
            return defaultReturnValue;
        }
    }else{
        return defaultReturnValue;
    }
}

void UI::TextView::DelegateEventHandler::textViewDidChange(Handle sender){
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.didChange){
            it->second.didChange();
        }
    }
}

void UI::TextView::DelegateEventHandler::textViewDidChangeSelection(Handle sender){
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.didChangeSelection){
            it->second.didChangeSelection();
        }
    }
}

bool UI::TextView::DelegateEventHandler::textViewShouldInteractWithTextAttachment(Handle sender, Handle textAttachment, NSRange characterRange){
    const auto defaultReturnValue=true;
    
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.shouldInteractWithTextAttachment){
            return it->second.shouldInteractWithTextAttachment(textAttachment, characterRange);
        }else{
            return defaultReturnValue;
        }
    }else{
        return defaultReturnValue;
    }
}

bool UI::TextView::DelegateEventHandler::textViewShouldInteractWithURL(Handle sender, Handle url, NSRange characterRange){
    const auto defaultReturnValue=true;
    
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        if(it->second.shouldInteractWithTextAttachment){
            return it->second.shouldInteractWithURL(url, characterRange);
        }else{
            return defaultReturnValue;
        }
    }else{
        return defaultReturnValue;
    }
}

void UI::TextView::setShouldBeginEditing(ShouldBeginEditing value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).shouldBeginEditing=value;
}

void UI::TextView::setDidBeginEditing(DidBeginEditing value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).didBeginEditing=value;
}

void UI::TextView::setShouldEndEditing(ShouldEndEditing value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).shouldEndEditing=value;
}

void UI::TextView::setDidEndEditing(DidEndEditing value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).didEndEditing=value;
}

void UI::TextView::setShouldChangeTextInRange(ShouldChangeTextInRange value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).shouldChangeTextInRange=value;
}

void UI::TextView::setDidChange(DidChange value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).didChange=value;
}

void UI::TextView::setDidChangeSelection(DidChangeSelection value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).didChangeSelection=value;
}

void UI::TextView::setShouldInteractWithTextAttachment(ShouldInteractWithTextAttachment value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).shouldInteractWithTextAttachment=value;
}

void UI::TextView::setShouldInteractWithURL(ShouldInteractWithURL value, const Viper::Disposable &disposable){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UITextViewDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
        
        DelegateEventHandler::disposablesMap[disposable.id].push_back(this->handle);
        Viper::Disposable::subscribe(&DelegateEventHandler::observer);
    }
    DelegateEventHandler::getOrCreate(this->handle).shouldInteractWithURL=value;
}

void UI::TextView::DelegateEventHandler::Observer::disposableDidDispose(Viper::Disposable::Id id){
    auto it=disposablesMap.find(id);
    if(it != disposablesMap.end()){
        auto &textViewHandles=it->second;
        for(auto textViewHandle:textViewHandles){
            auto delegateIt=delegateEventHandlers.find(textViewHandle);
            if(delegateIt != delegateEventHandlers.end()){
                delegateEventHandlers.erase(delegateIt);
            }
        }
        disposablesMap.erase(it);
    }
}

#endif  //__APPLE__
