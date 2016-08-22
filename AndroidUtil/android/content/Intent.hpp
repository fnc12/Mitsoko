
#ifndef __VIPER__ANDROID_UTIL__ANDROID__CONTENT__INTENT__
#define __VIPER__ANDROID_UTIL__ANDROID__CONTENT__INTENT__

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Viper/AndroidUtil/android/net/Uri.hpp"
#include "Viper/AndroidUtil/android/os/Bundle.hpp"
#include "Viper/AndroidUtil/android/net/Uri.hpp"
#include "Viper/AndroidUtil/java/lang/Class.hpp"
#include "Context.hpp"

namespace android{
    
    namespace content{
        
        struct Intent:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/content/Intent");
            
            static Intent create(const Context &context,const java::lang::Class &cls);
            
            static Intent create(const java::lang::String &action,const android::net::Uri &uri);
            
            static Intent create(const java::lang::String &action);
            
            static java::lang::String ACTION_PICK();
            
            android::net::Uri getData();
            
            android::os::Bundle getExtras();
            
            Intent& putExtra(const std::string &name,const std::string &value);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__CONTENT__INTENT__
