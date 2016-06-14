
#pragma once

#include "ViewController.hpp"
#include "Viper/iOSutil/NS/Array.hpp"

namespace UI {
    struct NavigationController:public ViewController{
        using ViewController::ViewController;
#ifdef __APPLE__
        STATIC_VAR(std::string, className, "UINavigationController");
        
        NS::Array viewControllers(){
            return this->sendMessage<Handle>("viewControllers");
        }
        
        void popToViewController(const ViewController &vc,bool animated){
            this->sendMessage<void>("popToViewController:animated:", vc.handle, animated);
        }
        
        void pushViewController(const ViewController &vc,bool animated){
            this->sendMessage<void>("pushViewController:animated:", vc.handle, animated);
        }
        
        void popViewControllerAnimated(bool animated){
            this->sendMessage<void>("popViewControllerAnimated:", animated);
        }
        
        static NavigationController create(const UI::ViewController &rootViewController){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "alloc");
            NavigationController res(handle);
            res.shouldClearOnDestroy=true;
            res.initWithRootViewController(rootViewController);
            return std::move(res);
        }
    protected:
        Handle initWithRootViewController(const Handle &rootViewController){
            return this->sendMessage<Handle>("initWithRootViewController:", rootViewController);
        }
#endif
    };
}
