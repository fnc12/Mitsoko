
#pragma once

#include "Responder.hpp"
#include "View.hpp"
#include "TabBarItem.hpp"
#include "NavigationItem.hpp"
#include <functional>

namespace UI {
    
    template<class NavC>
    struct _ViewController:public UI::Responder{
        using Responder::Responder;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        typedef _ViewController<NavC> Self;
        
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

template<class NavC>
const std::string UI::_ViewController<NavC>::className="UIViewController";

#endif  //__APPLE__
