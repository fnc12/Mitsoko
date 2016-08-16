
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__COLLECTION__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__COLLECTION__

#include "Iterable.hpp"

namespace java{
    namespace lang{
        
        /**
         *  Generic interface.
         */
        struct Collection:public Iterable{
            using Iterable::Iterable;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "java/lang/Collection");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__COLLECTION__
