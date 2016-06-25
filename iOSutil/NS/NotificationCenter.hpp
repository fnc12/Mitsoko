
#pragma once

#include "Object.hpp"
#include <functional>
#include <map>
#include "Viper/Disposable.hpp"
#include "String.hpp"

namespace NS {
    struct NotificationCenter:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(std::string, className, "NSNotificationCenter");
        
        static NotificationCenter defaultCenter(){
            auto cls=NS::getClass(className());
            return NS::Object::sendMessage<Handle>(cls,"defaultCenter");
        }
        
        //  todo..
        void addObserver(const Viper::Disposable &observer,std::function<void()> selector,NS::String name){
            
        }
        
    protected:
        
        
#endif
    };
}
