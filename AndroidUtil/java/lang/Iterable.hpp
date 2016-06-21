
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        
        /**
         *  Generic interface.
         */
        struct Iterable:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/lang/Iterable");
#endif
        };
    }
}
