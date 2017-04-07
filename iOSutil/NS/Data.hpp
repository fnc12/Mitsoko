
#ifndef __VIPER__IOS_UTIL__NS__DATA__
#define __VIPER__IOS_UTIL__NS__DATA__

#include "Object.hpp"
#include "Mitsoko/Util.hpp"
#include "Mitsoko/iOSutil/CF/String.hpp"

namespace NS {
    struct Data:public NS::Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        static NS::Data createWithContentsOfFile(const std::string &path);
        
        static NS::Data createWithContentsOfFile(const CF::String &path);
        
        int length();
        
        const void *bytes();
        
        bool writeToFile(const std::string &path,bool useAuxiliaryFile);
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__DATA__
