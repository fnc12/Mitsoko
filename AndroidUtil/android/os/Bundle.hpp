
#ifndef __VIPER__ANDROID_UTIL__ANDROID__OS__BUNDLE__
#define __VIPER__ANDROID_UTIL__ANDROID__OS__BUNDLE__

#include "BaseBundle.hpp"

namespace android{
    
    namespace os{
        
        struct Bundle:public BaseBundle{
            
            using BaseBundle::BaseBundle;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/os/Bundle");
            
#endif
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__OS__BUNDLE__
