
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__THREAD__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__THREAD__

#include "Object.hpp"
#include "Runnable.hpp"

namespace java{
    
    namespace lang{
        
        struct Thread : public Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/lang/Thread");
            
            void start();
            
            static Thread create(const Runnable &runnable);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__THREAD__
