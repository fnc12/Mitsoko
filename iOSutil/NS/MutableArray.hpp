
#pragma once

#include "Array.hpp"

namespace NS{
    struct MutableArray:public NS::Array{
        using Array::Array;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSMutableArray");
        
        static NS::MutableArray create(){
            /*auto res=NS::Object::create<NS::MutableArray>();
//            res.shouldClearOnDestroy=true;
            return std::move(res);*/
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "new");
            NS::MutableArray res(handle);
//            res.shouldClearOnDestroy=true;
            return std::move(res);
        }
        
        void addObject(const NS::Object &anObject){
            this->sendMessage<void>("addObject:", anObject.handle);
        }
#endif
    };
}
