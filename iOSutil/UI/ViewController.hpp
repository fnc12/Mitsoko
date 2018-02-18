
#ifndef __VIPER_APPLE_UI_VIEW_CONTROLLER_H
#define __VIPER_APPLE_UI_VIEW_CONTROLLER_H

#include "Responder.hpp"
#include "View.hpp"
#include "TabBarItem.hpp"
#include "NavigationItem.hpp"
#include <functional>

namespace UI {
    
    template<class NavC, class TabC>
    struct _ViewController : public UI::Responder {
        
        using Responder::Responder;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        using Self = _ViewController<NavC, TabC>;
        
        Self parentViewController() {
            return this->sendMessage<Handle>("parentViewController");
        }
        
        void setTabBarItem(const UI::TabBarItem &newValue){
            this->sendMessage<void>("setTabBarItem:",newValue.handle);
        }
        
        UI::TabBarItem tabBarItem(){
            return this->sendMessage<Handle>("tabBarItem");
        }
        
        UI::View view(){
            return this->sendMessage<Handle>("view");
        }
        
        NavigationItem navigationItem(){
            return this->sendMessage<Handle>("navigationItem");
        }
        
        NavC navigationController(){
            return this->sendMessage<Handle>("navigationController");
        }
        
        TabC tabBarController() {
            return this->sendMessage<Handle>("tabBarController");
        }
        
        void presentViewController(const Self &vc,bool animated,std::function<void()> completion){
            this->sendMessage<void>("presentViewController:animated:completion:", vc.handle, animated, ^{
                if(completion){
                    completion();
                }
            });
        }
        
        Self presentingViewController(){
            return this->sendMessage<Handle>("presentingViewController");
        }
        
        void dismissViewControllerAnimated(bool animated,std::function<void()> completion){
            this->sendMessage<void>("dismissViewControllerAnimated:completion:", animated, ^{
                if(completion){
                    completion();
                }
            });
        }
#endif
    };
}

#ifdef __APPLE__

template<class NavC, class TabC>
const std::string UI::_ViewController<NavC, TabC>::className = "UIViewController";

#endif  //__APPLE__

#endif /* __VIPER_APPLE_UI_VIEW_CONTROLLER_H */
