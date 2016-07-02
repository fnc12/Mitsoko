
#pragma once

#include "Map.hpp"

namespace java {
    namespace util{
        template<class K,class V>
        struct AbstractMap:public Map<K,V>{
            typedef Map<K,V> Super;
            using Super::Super;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/util/AbstractMap");
            
#endif
        };
    }
}
