
#pragma once

#include "Dictionary.hpp"

namespace NS {
    struct MutableDictionary:public NS::Dictionary{
        using Dictionary::Dictionary;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSMutableDictionary");
        
        void setObject(const NS::Object &anObject,const NS::Object &aKey){
            this->sendMessage<void>("setObject:forKey:", anObject.handle, aKey.handle);
        }
        
        void removeObjectForKey(const NS::Object &aKey){
            this->sendMessage<void>("removeObjectForKey:", aKey.handle);
        }
#endif
    };
}
