//
//  ImagePickerController.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ImagePickerController.hpp"

#ifdef __APPLE__

const std::string UI::ImagePickerController::className="UIImagePickerController";

UI::ImagePickerController::DelegateEventHandler::DelegateEventHandlersMap UI::ImagePickerController::DelegateEventHandler::delegateEventHandlers;

UI::ImagePickerController UI::ImagePickerController::create(){
    auto cls=NS::getClass(className);
    assert(cls);
    auto handle=sendMessage<Handle>(cls, "new");
    ImagePickerController res(handle);
    return std::move(res);
}

bool UI::ImagePickerController::isSourceTypeAvailable(UI::ImagePickerController::SourceType sourceType){
    auto cls=NS::getClass(className);
    return sendMessage<BOOL>(cls,"isSourceTypeAvailable:", UIImagePickerControllerSourceType(sourceType));
}

NS::Array UI::ImagePickerController::availableMediaTypesForSourceType(UI::ImagePickerController::SourceType sourceType){
    auto cls=NS::getClass(className);
    return sendMessage<Handle>(cls,"availableMediaTypesForSourceType:", UIImagePickerControllerSourceType(sourceType));
}

NS::String UI::ImagePickerController::OriginalImage(){
    auto res=CFBridgingRetain(UIImagePickerControllerOriginalImage);
    CFRelease(res);
    return res;
}

void UI::ImagePickerController::setDidCancel(DidCancel f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIImagePickerControllerDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).didCancel=f;
}

void UI::ImagePickerController::setDidFinishPickingMediaWithInfo(DidFinishPickingMediaWithInfo f){
    if(!DelegateEventHandler::get(this->handle)){
        auto sharedEventHandlerClass=NS::getClass("UIImagePickerControllerDelegateEventHandler");
        auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
        this->sendMessage<void>("setDelegate:", sharedEventHandler);
    }
    DelegateEventHandler::getOrCreate(this->handle).didFinishPickingMediaWithInfo=f;
}

void UI::ImagePickerController::setMediaTypes(const NS::Array &newValue){
    this->sendMessage<void>("setMediaTypes:", newValue.handle);
}

NS::Array UI::ImagePickerController::mediaTypes(){
    return this->sendMessage<Handle>("mediaTypes");
}

void UI::ImagePickerController::setSourceType(UI::ImagePickerController::SourceType newValue){
    this->sendMessage<void>("setSourceType:", UIImagePickerControllerSourceType(newValue));
}

auto UI::ImagePickerController::sourceType()->SourceType{
    return SourceType(this->sendMessage<UIImagePickerControllerSourceType>("sourceType"));
}

void UI::ImagePickerController::DelegateEventHandler::imagePickerControllerDidCancel(const void *sender){
    if(auto d=get(sender)){
        if(d->didCancel){
            d->didCancel(sender);
        }
        DelegateEventHandler::remove(sender);
    }
}

void UI::ImagePickerController::DelegateEventHandler::imagePickerControllerDidFinishPickingMediaWithInfo(const void *sender,const void *info){
    if(auto d=get(sender)){
        if(d->didFinishPickingMediaWithInfo){
            d->didFinishPickingMediaWithInfo(sender,info);
        }
        DelegateEventHandler::remove(sender);
    }
}

auto UI::ImagePickerController::DelegateEventHandler::getOrCreate(const void *sender)->DelegateEventHandler&{
    auto it=delegateEventHandlers.find(sender);
    if(it != delegateEventHandlers.end()){
        return it->second;
    }else{
        return delegateEventHandlers.insert({sender,{}}).first->second;
    }
}

auto UI::ImagePickerController::DelegateEventHandler::get(const void *aw)->DelegateEventHandler*{
    auto it=delegateEventHandlers.find(aw);
    if(it != delegateEventHandlers.end()){
        return &it->second;
    }else{
        return nullptr;
    }
}

void UI::ImagePickerController::DelegateEventHandler::remove(const void *aw){
    auto it=delegateEventHandlers.find(aw);
    if(it != delegateEventHandlers.end()){
        delegateEventHandlers.erase(it);
    }
}

#endif  //__APPLE__
