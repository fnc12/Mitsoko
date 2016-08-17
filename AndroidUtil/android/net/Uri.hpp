
#ifndef __VIPER__ANDROID_UTIL__ANDROID__NET__URI__
#define __VIPER__ANDROID_UTIL__ANDROID__NET__URI__

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android {
    
    namespace net{
        
        struct Uri:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/net/Uri");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__NET__URI__
