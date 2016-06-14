
#pragma once

#include "Object.hpp"

namespace NS {
    struct Array:public Object{
        using Object::Object;
#ifdef __APPLE__
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
