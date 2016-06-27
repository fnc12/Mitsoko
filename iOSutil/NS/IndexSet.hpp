
#pragma once

#include "Object.hpp"

namespace NS {
    struct IndexSet:public Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSIndexSet");
        
        static IndexSet create(int index){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "indexSetWithIndex:",NSUInteger(index));
            IndexSet res(handle);
//            res.shouldClearOnDestroy=true;
            return std::move(res);
        }
        
    protected:
        /*Handle initWithIndex(int index){
         return this->sendMessage<Handle>("initWithIndex:", NSUInteger(index));
         }*/
#endif
    };
}
