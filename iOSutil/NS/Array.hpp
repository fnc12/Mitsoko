
#ifndef __VIPER__IOS_UTIL__NS__ARRAY__
#define __VIPER__IOS_UTIL__NS__ARRAY__

#include "Object.hpp"

namespace NS {
    struct Array:public Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "NSArray");
        
        /*template<class ...Args>
        static NS::Array create(Args ...args);
        
        template<class T,class ...Args>
        static NS::Array create(T head,Args ...args){
            auto res=NS::Object::create<NS::Array>();
            res.shouldClearOnDestroy=true;
            return std::move(res);
        }*/
        
        int count();
        
        /**
         *  Operator replacement for `objectAtIndex:` function.
         */
        Handle operator[](int i);
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__ARRAY__
