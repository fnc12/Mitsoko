
#ifndef __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP_FACTORY__
#define __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP_FACTORY__

#include "Mitsoko/AndroidUtil/java/lang/Array.hpp"
#include "Mitsoko/AndroidUtil/java/lang/String.hpp"
#include "Bitmap.hpp"
#include "ColorSpace.hpp"

namespace android {
    
    namespace graphics {
        
        struct BitmapFactory : public java::lang::Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            struct Options : public java::lang::Object {
                
                using Object::Object;
                
                static const std::string signature;
                
                static Options create();
                
                Bitmap inBitmap();
                
                void inBitmap(Bitmap value);
                
                int inDensity();
                
                void inDensity(int value);
                
                bool inDither();
                
                void inDither(bool value);
                
                bool inInputShareable();
                
                void inInputShareable(bool value);
                
                bool inJustDecodeBounds();
                
                void inJustDecodeBounds(bool value);
                
                bool inMutable();
                
                void inMutable(bool value);
                
                bool inPreferQualityOverSpeed();
                
                void inPreferQualityOverSpeed(bool value);
                
                ColorSpace inPreferredColorSpace();
                
                void inPreferredColorSpace(ColorSpace value);
                
                Bitmap::Config inPreferredConfig();
                
                void inPreferredConfig(Bitmap::Config value);
                
            };
            
            static const std::string signature;
            
            static Bitmap decodeFile(const std::string &pathName);
            
            static Bitmap decodeFile(const java::lang::String &pathName);
            
            static Bitmap decodeFile(const java::lang::String &pathName, Options opts);
            
            static Bitmap decodeByteArray(java::lang::Array<char> data, int offset, int length);
            
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP_FACTORY__
