//
//  NavigationController.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "NavigationController.hpp"

#ifdef __APPLE__

const std::string UI::NavigationController::className="UINavigationController";

UI::NavigationController UI::NavigationController::create(const UI::ViewController &rootViewController){
    auto cls=NS::getClass(className);
    assert(cls);
    auto handle=sendMessage<Handle>(cls, "alloc");
    NavigationController res(handle);
    res.initWithRootViewController(rootViewController);
    return std::move(res);
}

UI::NavigationBar UI::NavigationController::navigationBar(){
    return this->sendMessage<Handle>("navigationBar");
}

void UI::NavigationController::setNavigationBarHidden(bool hidden){
    this->sendMessage<void>("setNavigationBarHidden:", BOOL(hidden));
}

bool UI::NavigationController::navigationBarHidden(){
    return this->sendMessage<BOOL>("navigationBarHidden");
}

void UI::NavigationController::setNavigationBarHidden(bool hidden,bool animated){
    this->sendMessage<void>("setNavigationBarHidden:animated:", BOOL(hidden),BOOL(animated));
}

void UI::NavigationController::popToViewController(const ViewController &vc,bool animated){
    this->sendMessage<void>("popToViewController:animated:", vc.handle, animated);
}

void UI::NavigationController::pushViewController(const ViewController &vc,bool animated){
    this->sendMessage<void>("pushViewController:animated:", vc.handle, animated);
}

void UI::NavigationController::popViewControllerAnimated(bool animated){
    this->sendMessage<void>("popViewControllerAnimated:", animated);
}

auto UI::NavigationController::initWithRootViewController(const Handle &rootViewController)->Handle{
    return this->sendMessage<Handle>("initWithRootViewController:", rootViewController);
}

#endif  //__APPLE__
