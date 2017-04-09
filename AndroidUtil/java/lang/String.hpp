
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__STRING__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__STRING__

#include "Object.hpp"
#include "CharSequence.hpp"

namespace java{
    
    namespace lang{
        
        struct String : public _CharSequence<String> {
            
            using _CharSequence::_CharSequence;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/lang/String");
            
            const char* c_str() const;
            
            static String create(std::string str);
            
#endif  //__ANDROID__
            
        };
        
        typedef _CharSequence<String> CharSequence;
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__STRING__
