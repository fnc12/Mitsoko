
#pragma once

#include "Collection.hpp"

namespace java{
    namespace lang{
        
        /**
         *  Generic interface.
         */
        struct List:public Collection{
            using Collection::Collection;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/lang/List");
#endif
        };
    }
}
