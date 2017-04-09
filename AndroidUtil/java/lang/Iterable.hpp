
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__ITERABLE__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__ITERABLE__

#include "Object.hpp"

namespace java{
    namespace lang{
        
        /**
         *  Generic interface.
         */
        struct Iterable : public java::lang::Object {
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/lang/Iterable");
            
#endif  //__ANDROID__
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__ITERABLE__
