
#ifndef __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP_FACTORY__
#define __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP_FACTORY__

#include "Mitsoko/AndroidUtil/java/lang/String.hpp"
#include "Bitmap.hpp"

namespace android {
    
    namespace graphics {
        
        struct BitmapFactory:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/graphics/BitmapFactory");
            
            static Bitmap decodeFile(const std::string &pathName);
            
            static Bitmap decodeFile(const java::lang::String &pathName);
            
            struct Options:public java::lang::Object{
                
                using Object::Object;
                
//            const std::string signature;
                STATIC_VAR(const std::string, signature, "android/graphics/BitmapFactory$Options");
                
                static Options create();
                
                /**
                 *  Enum setter
                 */
                /*void inPreferredConfig(int value){
                    this->setField<Bitmap::Config>("inPreferredConfig",value);
                }*/
                
            };
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP_FACTORY__
