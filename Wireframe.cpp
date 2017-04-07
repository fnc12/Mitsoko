//
//  Wireframe.cpp
//  Jako
//
//  Created by John Zakharov on 28.02.17.
//  Copyright © 2017 Outlaw Studio. All rights reserved.
//

#include "Wireframe.hpp"

//using android::content::Intent;
//using android::app::Activity;

void Mitsoko::NavigationPusher::operator()(const void *handle, const std::string &viewName) {
#ifdef __APPLE__
    UI::ViewController vc(handle);
    auto object = NS::Object::create<UI::ViewController>(viewName);
    vc.navigationController().pushViewController(object, true);
#endif
}

Mitsoko::NavigationClassPoper::NavigationClassPoper(const std::string &target_, bool animated_):
targetClassName(target_),
animated(animated_)
{
    //..
}

void Mitsoko::NavigationClassPoper::operator()(const void *handle) {
#ifdef __APPLE__
    UI::ViewController vc(handle);
    auto navigationController = vc.navigationController();
    auto viewControllers = navigationController.viewControllers();
    auto viewControllersCount = viewControllers.count();
    UI::ViewController targetVC = nullptr;
//    auto targetClassName = "Jako.JKMainTabBarC";
    for(auto i = viewControllersCount - 1; i; --i) {
        UI::ViewController vc = viewControllers[i];
        auto vcClass = vc.getClass();
        auto className = NSStringFromClass(vcClass);
        auto c_className = className.UTF8String;
        if(::strcmp(this->targetClassName.c_str(), c_className) == 0) {
            targetVC = std::move(vc);
            break;
        }
    }
    if(targetVC){
        navigationController.popToViewController(targetVC, true);
    }
#endif
}

void Mitsoko::FragmentStarter::operator()(const void *handle, const std::string &viewName) {
#ifdef __ANDROID__
    android::app::Fragment fragment(handle);
    auto activity = fragment.getActivity();
    java::lang::Class cls = java::lang::Class::find(viewName);
    auto intent = android::content::Intent::create(activity,cls);
    activity.startActivity(intent);
#endif
}

void Mitsoko::ActivityStarter::operator()(const void *handle, const std::string &viewName) {
#ifdef __ANDROID__
    android::app::Activity activity(handle);
    java::lang::Class cls = java::lang::Class::find(viewName);
    auto intent = android::content::Intent::create(activity, cls);
    if(this->result){
        activity.startActivityForResult(intent, *this->result);
    }else{
        activity.startActivity(intent);
    }
    if(this->finishSelf) {
        activity.finish();
    }
#endif
}

Mitsoko::ActivityCloser::ActivityCloser(){}

Mitsoko::ActivityCloser::ActivityCloser(int result_):result(std::make_shared<int>(result_)){}

void Mitsoko::ActivityCloser::operator()(const void *handle) {
#ifdef __ANDROID__
    android::app::Activity activity(handle);
    if(this->result){
        activity.setResult(*this->result);
    }
    activity.finish();
#endif
}

void Mitsoko::NavigationPoper::operator()(const void *handle) {
#ifdef __APPLE__
    UI::ViewController vc(handle);
    vc.navigationController().popViewControllerAnimated(this->animated);
#endif
}
