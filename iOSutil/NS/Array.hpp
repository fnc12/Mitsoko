
#pragma once

#include "Object.hpp"

namespace NS {
    struct Array:public Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSArray");
        
        /*template<class ...Args>
        static NS::Array create(Args ...args);
        
        template<class T,class ...Args>
        static NS::Array create(T head,Args ...args){
            auto res=NS::Object::create<NS::Array>();
            res.shouldClearOnDestroy=true;
            return std::move(res);
        }*/
        
        int count(){
            return int(this->sendMessage<NSUInteger>("count"));
        }
        
        /**
         *  Operator replacement for `objectAtIndex:` function.
         */
        Handle operator[](int i){
            return this->sendMessage<Handle>("objectAtIndex:", NSUInteger(i));
        }
#endif
    };
}
