
#ifndef __VIPER__IOS_UTIL__NS__MUTABLE_ARRAY__
#define __VIPER__IOS_UTIL__NS__MUTABLE_ARRAY__

#include "Array.hpp"

namespace NS{
    
    struct MutableArray : public NS::Array {
        
        using Array::Array;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "NSMutableArray");
        
        static NS::MutableArray create();
        
        static NS::MutableArray createWithCapacity(int capacity);
        
        void addObject(const NS::Object &anObject);
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__MUTABLE_ARRAY__
