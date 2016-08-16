
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__RUNNABLE__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__RUNNABLE__

#include "Object.hpp"

namespace java{
    namespace lang{
        struct Runnable:public Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "java/lang/Runnable");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__RUNNABLE__
