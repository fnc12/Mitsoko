//
//  BarButtonItem.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "BarButtonItem.hpp"

#ifdef __APPLE__

const std::string UI::BarButtonItem::className="UIBarButtonItem";

UI::BarButtonItem::TouchedMap UI::BarButtonItem::touchedMap;

UI::BarButtonItem::DisposablesMap UI::BarButtonItem::disposablesMap;

UI::BarButtonItem::Observer UI::BarButtonItem::observer;

UI::BarButtonItem UI::BarButtonItem::create(BarButtonSystemItem systemItem,
                                            Touched f,
                                            const Viper::Disposable *disposable)
{
    auto cls = NS::getClass(className);
    assert(cls);
    auto handle = sendMessage<Handle>(cls, "alloc");
    BarButtonItem res(handle);
    NS::Object target;
    SEL action = nil;
    if(f && disposable){
        cls = NS::getClass("UIBarButtonItemEventHandler");
        assert(cls);
        auto sharedEventHandler = NS::Object::sendMessage<Handle>(cls, "shared");
        assert(sharedEventHandler);
        target = sharedEventHandler;
        action=sel_getUid("barButtonItemTouched:");
        assert(action);
        touchedMap.insert({res.handle, f});
        disposablesMap.insert({disposable->id, res.handle});
        Viper::Disposable::subscribe(&observer);
    }
    res.initWithSystemItem(systemItem, target, action);
    return res;
}

UI::BarButtonItem UI::BarButtonItem::create(const UI::Image &image,Style style,Touched f,const Viper::Disposable *disposable){
    auto cls = NS::getClass(className);
    assert(cls);
    auto handle = sendMessage<Handle>(cls, "alloc");
    BarButtonItem res(handle);
    NS::Object target;
    SEL action = nil;
    if(f && disposable){
        cls = NS::getClass("UIBarButtonItemEventHandler");
        assert(cls);
        auto sharedEventHandler = NS::Object::sendMessage<Handle>(cls, "shared");
        assert(sharedEventHandler);
        target = sharedEventHandler;
        action=sel_getUid("barButtonItemTouched:");
        assert(action);
        touchedMap.insert({res.handle, f});
        disposablesMap.insert({disposable->id, res.handle});
        Viper::Disposable::subscribe(&observer);
    }
    res.initWithImage(image, style, target, action);
    return res;
}

UI::BarButtonItem UI::BarButtonItem::create(const std::string &title,Style style,Touched f,const Viper::Disposable *disposable){
    auto cls = NS::getClass(className);
    assert(cls);
    auto handle = sendMessage<Handle>(cls, "alloc");
    BarButtonItem res(handle);
    auto t = CF::String::create(title);
    NS::Object target;
    SEL action = nil;
    if(f && disposable){
        cls = NS::getClass("UIBarButtonItemEventHandler");
        assert(cls);
        auto sharedEventHandler = NS::Object::sendMessage<Handle>(cls, "shared");
        assert(sharedEventHandler);
        target = sharedEventHandler;
        action = sel_getUid("barButtonItemTouched:");
        assert(action);
        touchedMap.insert({res.handle, f});
        disposablesMap.insert({disposable->id, res.handle});
        Viper::Disposable::subscribe(&observer);
    }
    res.initWithTitle(t, style, target, action);
    return res;
}

void UI::BarButtonItem::touched(Handle handle){
    auto it=touchedMap.find(handle);
    if(it != touchedMap.end()){
        it->second(handle);
    }else{
        std::cerr<<"touched callback not found for UI::BarButtonItem for handle "<<handle<<std::endl;
    }
}

void UI::BarButtonItem::Observer::disposableDidDispose(Viper::Disposable::Id id){
    auto it=disposablesMap.find(id);
    if(it != disposablesMap.end()){
        auto handle=it->second;
        disposablesMap.erase(it);
        auto it2=touchedMap.find(handle);
        if(it2 != touchedMap.end()){
            touchedMap.erase(it2);
        }
        Viper::Disposable::unsubscribe(&observer);
    }
}

auto UI::BarButtonItem::initWithSystemItem(UI::BarButtonSystemItem systemItem,
                                           const NS::Object &target,
                                           SEL action) -> Handle
{
    return this->sendMessage<Handle>("initWithBarButtonSystemItem:target:action:",
                                     UIBarButtonSystemItem(systemItem),
                                     target.handle,
                                     action);
}

auto UI::BarButtonItem::initWithImage(const UI::Image &image,
                                      Style style,
                                      const NS::Object &target,
                                      SEL action) -> Handle
{
    return this->sendMessage<Handle>("initWithImage:style:target:action:",
                                     image.handle,
                                     UIBarButtonItemStyle(style),
                                     target.handle,
                                     action);
}

auto UI::BarButtonItem::initWithTitle(const CF::String &title,
                                      Style style,
                                      const NS::Object &target,
                                      SEL action) -> Handle
{
    return this->sendMessage<Handle>("initWithTitle:style:target:action:",
                                     title.handle,
                                     UIBarButtonItemStyle(style),
                                     target.handle,
                                     action);
}

#endif  //__APPLE__
