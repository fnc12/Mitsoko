
#ifndef __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP__
#define __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP__

#include "Mitsoko/AndroidUtil/java/lang/Object.hpp"
#include "Mitsoko/AndroidUtil/java/io/OutputStream.hpp"

namespace android {
    
    namespace graphics {
        
        struct Bitmap : public java::lang::Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            int getWidth();
            
            int getHeight();
            
            void recycle();
            
            void setHasAlpha(bool hasAlpha);
            
            struct CompressFormat : public java::lang::Object {
                
                using Object::Object;
                
                static const std::string signature;
                
                static CompressFormat JPEG();
                
                static CompressFormat PNG();
                
                static int WEBP();
            };
            
            struct Config : public java::lang::Object {
                
                using Object::Object;
                
                static const std::string signature;
                
                static Config ALPHA_8();
                
                static Config RGB_565();
                
                static Config ARGB_4444();
                
                static Config ARGB_8888();
            };
            
            bool compress(CompressFormat format, int quality, const java::io::OutputStream &stream);
            
            static Bitmap createScaledBitmap(const Bitmap &src, int dstWidth, int dstHeight, bool filter);
            
            static Bitmap createBitmap(const Bitmap &source,
                                       int x,
                                       int y,
                                       int width,
                                       int height);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP__
