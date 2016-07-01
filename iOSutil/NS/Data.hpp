
#pragma once

#include "Object.hpp"

namespace NS {
    struct Data:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSData");
        
        static NS::Data createWithContentsOfFile(const std::string &path){
            auto s=CF::String::create(path);
            return std::move(createWithContentsOfFile(s));
        }
        
        static NS::Data createWithContentsOfFile(const CF::String &path){
            auto cls=NS::getClass(className());
            assert(cls);
            return sendMessage<Handle>(cls, "dataWithContentsOfFile:",path.handle);
        }
        
        int length(){
            return int(this->sendMessage<NSUInteger>("length"));
        }
        
        const void *bytes(){
            return this->sendMessage<const void*>("bytes");
        }
        
        bool writeToFile(const std::string &path,bool useAuxiliaryFile){
            auto p=CF::String::create(path);
            return this->sendMessage<BOOL>("writeToFile:atomically:", p.handle, BOOL(useAuxiliaryFile));
        }
#endif
    };
}
