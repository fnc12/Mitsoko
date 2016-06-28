
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/Util.hpp"

namespace NS {
    struct Dictionary:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSDictionary");
        
        /*Handle operator[](const NS::Object &aKey){
            return this->objectForKey(aKey);
        }*/
        
        Handle objectForKey(const NS::Object &aKey){
            return this->sendMessage<Handle>("objectForKey:", aKey.handle);
        }
        
        int count(){
            return int(this->sendMessage<NSUInteger>("count"));
        }
#endif
    };
}
