
#pragma once

#include "Responder.hpp"
#include "View.hpp"

namespace UI {
    struct ViewController:public UI::Responder{
        using Responder::Responder;
#ifdef __APPLE__
        
        UI::View view(){
            return this->sendMessage<Handle>("view");
        }
        
        NavigationItem navigationItem(){
            return this->sendMessage<Handle>("navigationItem");
        }
        
        Handle navigationController(){
            return this->sendMessage<Handle>("navigationController");
        }
        
        void presentViewController(const ViewController &vc,bool animated){
            this->sendMessage<void>("presentViewController:animated:completion:", vc.handle, animated);
        }
        
        ViewController presentingViewController(){
            return this->sendMessage<Handle>("presentingViewController");
        }
        
        void dismissViewControllerAnimated(bool animated){
            this->sendMessage<void>("dismissViewControllerAnimated:completion:", animated, nullptr);
        }
#endif
    };
}
