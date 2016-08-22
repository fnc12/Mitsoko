
#ifndef __VIPER__ANDROID_UTIL__JAVA__UTIL__ABSTRACT_MAP__
#define __VIPER__ANDROID_UTIL__JAVA__UTIL__ABSTRACT_MAP__

#include "Map.hpp"

namespace java {
    
    namespace util{
        
        template<class K,class V>
        struct AbstractMap:public Map<K,V>{
            
            typedef Map<K,V> Super;
            
            using Super::Super;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "java/util/AbstractMap");
            
#endif  //__ANDROID__
            
        };
    }
}

#ifdef __ANDROID__

/*template<class K,class V>
 const std::string java::util::AbstractMap<K,V>::signature="java/util/AbstractMap";*/

#endif  //__ANDROID__

#endif  //__VIPER__ANDROID_UTIL__JAVA__UTIL__ABSTRACT_MAP__
