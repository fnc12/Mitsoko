
#ifndef __VIPER__ANDROID_UTIL__ANDROID__OS__HANDLER__
#define __VIPER__ANDROID_UTIL__ANDROID__OS__HANDLER__

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/java/lang/Runnable.hpp"

namespace android{
    
    namespace os{
        
        struct Handler:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/os/Handler");
            
            bool post(const java::lang::Runnable &runnable);
            
            static Handler create();
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__OS__HANDLER__
