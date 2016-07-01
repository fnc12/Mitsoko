
#pragma once

#include "ViewController.hpp"
#include "Viper/iOSutil/NS/Array.hpp"
#include "NavigationBar.hpp"

namespace UI {
    struct NavigationController;
    typedef _ViewController<NavigationController> ViewController;
    
    struct NavigationController:public _ViewController<NavigationController>{
        using _ViewController::_ViewController;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UINavigationController");
        
        static NavigationController create(const UI::ViewController &rootViewController){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "alloc");
            NavigationController res(handle);
            res.initWithRootViewController(rootViewController);
            return std::move(res);
        }
        
        UI::NavigationBar navigationBar(){
            return this->sendMessage<Handle>("navigationBar");
        }
        
        void setNavigationBarHidden(bool hidden){
            this->sendMessage<void>("setNavigationBarHidden:", BOOL(hidden));
        }
        
        bool navigationBarHidden(){
            return this->sendMessage<BOOL>("navigationBarHidden");
        }
        
        void setNavigationBarHidden(bool hidden,bool animated){
            this->sendMessage<void>("setNavigationBarHidden:animated:", BOOL(hidden),BOOL(animated));
        }
        
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
    protected:
        Handle initWithRootViewController(const Handle &rootViewController){
            return this->sendMessage<Handle>("initWithRootViewController:", rootViewController);
        }
#endif
    };
}
