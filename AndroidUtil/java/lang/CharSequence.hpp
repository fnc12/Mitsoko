
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__CHAR_SEQUENCE__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__CHAR_SEQUENCE__

#include "Object.hpp"

namespace java{
    
    namespace lang{
        
        /**
         *  S must be java::lang::String. Template used to solve two headers include each other problem.
         */
        template<class S>
        struct _CharSequence : public Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/lang/CharSequence");
            
            S toString(){
                return this->sendMessage<S>("toString");
            }
#endif  //__ANDROID__
        };

#ifdef __ANDROID__
        
        template<class S>
        const std::string _CharSequence<S>::signature = "java/lang/CharSequence";
#endif  //__ANDROID__
        
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__CHAR_SEQUENCE__
