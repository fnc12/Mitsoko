
#pragma once

#include "Object.hpp"
#include "Array.hpp"

namespace NS {
    struct Bundle:public Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSBundle");
        
        static Bundle mainBundle(){
            auto cls=NS::getClass(className());
            assert(cls);
            return sendMessage<Handle>(cls, "mainBundle");
        }
        
        NS::Array preferredLocalizations(){
            return this->sendMessage<Handle>("preferredLocalizations");
        }
#endif
    };
}
