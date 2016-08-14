
#ifndef __VIPER__IOS_UTIL__NS__INDEX_SET__
#define __VIPER__IOS_UTIL__NS__INDEX_SET__

#include "Object.hpp"

namespace NS {
    struct IndexSet:public Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "NSIndexSet");
        
        static IndexSet create(int index);
        
    protected:
        /*Handle initWithIndex(int index){
         return this->sendMessage<Handle>("initWithIndex:", NSUInteger(index));
         }*/
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__INDEX_SET__
