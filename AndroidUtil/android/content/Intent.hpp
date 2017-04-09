
#ifndef __VIPER__ANDROID_UTIL__ANDROID__CONTENT__INTENT__
#define __VIPER__ANDROID_UTIL__ANDROID__CONTENT__INTENT__

#include "Mitsoko/AndroidUtil/java/lang/Object.hpp"
#include "Mitsoko/AndroidUtil/java/lang/String.hpp"
#include "Mitsoko/AndroidUtil/android/net/Uri.hpp"
#include "Mitsoko/AndroidUtil/android/os/Bundle.hpp"
#include "Mitsoko/AndroidUtil/android/net/Uri.hpp"
#include "Mitsoko/AndroidUtil/java/lang/Class.hpp"
#include "Context.hpp"

#include <vector>
#include <initializer_list>

namespace android{
    
    namespace content{
        
        struct Intent : public java::lang::Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/content/Intent");
            
            static Intent create(const Context &context, const java::lang::Class &cls);
            
            static Intent create(const java::lang::String &action, const android::net::Uri &uri);
            
            static Intent create(const java::lang::String &action);
            
            static java::lang::String ACTION_PICK();
            
            static java::lang::String ACTION_CALL();
            
            static java::lang::String ACTION_SEND();
            
            static java::lang::String EXTRA_EMAIL();
            
            static java::lang::String EXTRA_SUBJECT();
            
            static java::lang::String EXTRA_TEXT();
            
            static Intent createChooser(const Intent &target, const std::string &title);
            
            Intent& setType(const std::string &type);
            
            android::net::Uri getData();
            
            android::os::Bundle getExtras();
            
            Intent& putExtra(const std::string &name, const std::string &value);
            
            Intent& putExtra(const std::string &name, const std::vector<std::string> &value);
            
            Intent& setData(const android::net::Uri &data);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__CONTENT__INTENT__
