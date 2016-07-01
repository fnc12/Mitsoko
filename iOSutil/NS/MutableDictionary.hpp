
#pragma once

#include "Dictionary.hpp"

namespace NS {
    struct MutableDictionary:public NS::Dictionary{
        using Dictionary::Dictionary;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSMutableDictionary");
        
        static NS::MutableDictionary create(){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "new");
//            Handle res=handle;
            return handle;
        }
        
        void setObject(const NS::Object &anObject,const NS::Object &aKey){
            this->sendMessage<void>("setObject:forKey:", anObject.handle, aKey.handle);
        }
        
        void removeObjectForKey(const NS::Object &aKey){
            this->sendMessage<void>("removeObjectForKey:", aKey.handle);
        }
#endif
    };
}
