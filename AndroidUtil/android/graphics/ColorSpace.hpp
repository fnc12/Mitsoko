
#ifndef __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__COLOR_SPACE__
#define __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__COLOR_SPACE__

#include "Mitsoko/AndroidUtil/java/lang/Object.hpp"

namespace android {
    
    namespace graphics {
        
        struct ColorSpace : public java::lang::Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            
            
#endif  //  __ANDROID__
            
        };
    }
}

#endif  //  __VIPER__ANDROID_UTIL__ANDROID__GRAPHICS__COLOR_SPACE__
