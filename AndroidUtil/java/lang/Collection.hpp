
#pragma once

#include "Iterable.hpp"

namespace java{
    namespace lang{
        
        /**
         *  Generic interface.
         */
        struct Collection:public Iterable{
            using Iterable::Iterable;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/lang/Collection");
#endif
        };
    }
}
