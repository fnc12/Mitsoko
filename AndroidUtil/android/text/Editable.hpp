
#ifndef __VIPER__ANDROID_UTIL__ANDROID__TEXT__EDITABLE__
#define __VIPER__ANDROID_UTIL__ANDROID__TEXT__EDITABLE__

#include "Mitsoko/AndroidUtil/java/lang/String.hpp"

namespace android{
    
    namespace text{
        
        struct Editable : public java::lang::_CharSequence<java::lang::String> {
            
            using _CharSequence::_CharSequence;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__TEXT__EDITABLE__
