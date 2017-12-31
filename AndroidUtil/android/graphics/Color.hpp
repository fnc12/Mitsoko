
#ifndef __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__COLOR__
#define __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__COLOR__

#include "Mitsoko/AndroidUtil/java/lang/Object.hpp"

namespace android {
    
    namespace graphics {
        
        struct Color : public java::lang::Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            static int BLACK();
            
            static int DKGRAY();
            
            static int GRAY();
            
            static int LTGRAY();
            
            static int WHITE();
            
            static int RED();
            
            static int GREEN();
            
            static int BLUE();
            
            static int YELLOW();
            
            static int CYAN();
            
            static int MAGENTA();
            
            static int TRANSPARENT();
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__COLOR__
