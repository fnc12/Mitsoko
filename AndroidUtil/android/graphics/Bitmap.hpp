
#ifndef __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP__
#define __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP__

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/java/io/OutputStream.hpp"

namespace android {
    
    namespace graphics {
        
        struct Bitmap:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/graphics/Bitmap");
            
            int getWidth();
            
            int getHeight();
            
            struct CompressFormat:public java::lang::Object{
                
                using Object::Object;
                
//            const std::string signature;
                STATIC_VAR(const std::string, signature, "android/graphics/Bitmap$CompressFormat");
                
                static int JPEG();
                
                static int PNG();
                
                static int WEBP();
            };
            
            struct Config:public java::lang::Object{
                
                using Object::Object;
                
//            const std::string signature;
                STATIC_VAR(const std::string, signature, "android/graphics/Bitmap$Config");
                
                static int ALPHA_8();
                
                static int RGB_565();
                
                static int ARGB_4444();
                
                static int ARGB_8888();
            };
            
            bool compress(int format,int quality,const java::io::OutputStream &stream);
            
            static Bitmap createScaledBitmap(const Bitmap &src, int dstWidth, int dstHeight, bool filter);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__BITMAP__
