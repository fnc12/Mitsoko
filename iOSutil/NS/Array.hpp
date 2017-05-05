
#ifndef __VIPER__IOS_UTIL__NS__ARRAY__
#define __VIPER__IOS_UTIL__NS__ARRAY__

#include "Object.hpp"

namespace NS {
    
    struct Array : public Object {
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        int count();
        
        /**
         *  Operator replacement for `objectAtIndex:` function.
         */
        Handle operator[](int i);
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__ARRAY__
