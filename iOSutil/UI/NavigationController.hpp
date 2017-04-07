
#ifndef __VIPER__IOS_UTIL__UI__NAVIGATION_CONTROLLER__
#define __VIPER__IOS_UTIL__UI__NAVIGATION_CONTROLLER__

#include "ViewController.hpp"
#include "Mitsoko/iOSutil/NS/Array.hpp"
#include "NavigationBar.hpp"

namespace UI {
    struct NavigationController;
    typedef _ViewController<NavigationController> ViewController;
    
    struct NavigationController : public _ViewController<NavigationController> {
        
        using _ViewController::_ViewController;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UINavigationController");
        
        static NavigationController create(const UI::ViewController &rootViewController);
        
        UI::NavigationBar navigationBar();
        
        void setNavigationBarHidden(bool hidden);
        
        bool navigationBarHidden();
        
        void setNavigationBarHidden(bool hidden,bool animated);
        
        NS::Array viewControllers(){
            return this->sendMessage<Handle>("viewControllers");
        }
        
        void popToViewController(const ViewController &vc,bool animated);
        
        void pushViewController(const ViewController &vc,bool animated);
        
        void popViewControllerAnimated(bool animated);
    protected:
        Handle initWithRootViewController(const Handle &rootViewController);
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__NAVIGATION_CONTROLLER__
