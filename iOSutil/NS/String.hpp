
#ifndef __VIPER__IOS_UTIL__NS__STRING__
#define __VIPER__IOS_UTIL__NS__STRING__

#include "Object.hpp"
#include "Viper/Util.hpp"

namespace NS {
    struct String:public NS::Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
//        STATIC_VAR(std::string, className, "NSString");
        
        const char* UTF8String();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__STRING__
