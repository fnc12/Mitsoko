
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__LIST__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__LIST__

#include "Collection.hpp"

namespace java{
    
    namespace lang{
        
        /**
         *  Generic interface.
         */
        struct List : public Collection {
            
            using Collection::Collection;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/lang/List");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__LIST__
