
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace android {
    namespace provider {
        struct MediaStore:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/provider/MediaStore");
            
            static java::lang::String ACTION_IMAGE_CAPTURE(){
                if(java::lang::Class cls=java::lang::Class::find<MediaStore>()){
                    return cls.getStaticField<java::lang::String>("ACTION_IMAGE_CAPTURE");
                }else{
                    return {};
                }
            }
            
            struct Images:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/provider/MediaStore$Images");
                
                struct Media:public java::lang::Object{
                    using Object::Object;
                    STATIC_VAR(const std::string, signature, "android/provider/MediaStore$Images$Media");
                    
                    static android::net::Uri EXTERNAL_CONTENT_URI(){
                        if(java::lang::Class cls=java::lang::Class::find<Media>()){
                            return cls.getStaticField<android::net::Uri>("EXTERNAL_CONTENT_URI");
                        }else{
                            return {};
                        }
                    }
                };
            };
#endif
        };
    }
}
