
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
    struct Application:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIApplication");
        
        static Application sharedApplication(){
            auto cls=NS::getClass(className());
            return NS::Object::sendMessage<Handle>(cls,"sharedApplication");
        }
        
        bool networkActivityIndicatorVisible(){
            return this->sendMessage<bool>("networkActivityIndicatorVisible");
        }
        
        void setNetworkActivityIndicatorVisible(bool newValue){
            this->sendMessage<void>("setNetworkActivityIndicatorVisible:", newValue);
        }
        
#endif
    };
}
