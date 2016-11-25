
#ifndef __VIPER__IOS_UTIL__NS__BUNDLE__
#define __VIPER__IOS_UTIL__NS__BUNDLE__

#include "Object.hpp"
#include "Array.hpp"
#include "String.hpp"

namespace NS {
    struct Bundle:public Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "NSBundle");
        
        static Bundle mainBundle();
        
        std::string pathForResource(const std::string &name, const std::string &ext);
        
        NS::Array preferredLocalizations();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__BUNDLE__
