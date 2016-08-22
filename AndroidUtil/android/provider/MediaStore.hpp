
#ifndef __VIPER__ANDROID_UTIL__ANDROID__PROVIDER__MEDIA_STORE__
#define __VIPER__ANDROID_UTIL__ANDROID__PROVIDER__MEDIA_STORE__

#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Viper/AndroidUtil/android/net/Uri.hpp"

namespace android {
    
    namespace provider {
        
        struct MediaStore:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/provider/MediaStore");
            
            static java::lang::String ACTION_IMAGE_CAPTURE();
            
            struct Images:public java::lang::Object{
                
                using Object::Object;
                
//            const std::string signature;
                STATIC_VAR(const std::string, signature, "android/provider/MediaStore$Images");
                
                struct Media:public java::lang::Object{
                    
                    using Object::Object;
                    
//            const std::string signature;
                    STATIC_VAR(const std::string, signature, "android/provider/MediaStore$Images$Media");
                    
                    static android::net::Uri EXTERNAL_CONTENT_URI();
                };
            };
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__PROVIDER__MEDIA_STORE__
