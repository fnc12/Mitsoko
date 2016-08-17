
#ifndef __VIPER__ANDROID_UTIL__ANDROID__CONTENT__CONTEXT__
#define __VIPER__ANDROID_UTIL__ANDROID__CONTENT__CONTEXT__

#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Viper/AndroidUtil/android/content/res/Resources.hpp"

namespace android{
    
    namespace content{
        
        struct Context:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/content/Context");
            
            res::Resources getResources();
            
            java::lang::String getPackageName();
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__CONTENT__CONTEXT__
