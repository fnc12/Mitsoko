
#pragma once

#include "NavigationController.hpp"
#include "Viper/iOSutil/NS/Array.hpp"

namespace UI{
    struct TabBarController:public _ViewController<NavigationController>{
        using _ViewController::_ViewController;
#ifdef __APPLE__
        STATIC_VAR(std::string, className, "UITabBarController");
        
        void setViewControllers(const NS::Array &newValue){
            this->sendMessage<void>("setViewControllers:", newValue.handle);
        }
        
        NS::Array viewControllers(){
            return this->sendMessage<Handle>("viewControllers");
        }
#endif

    };
}
