
#pragma once

#include "Object.hpp"
#include "Viper/Util.hpp"

namespace NS {
    struct String:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(std::string, className, "NSString");
        
        const char* UTF8String(){
            return this->sendMessage<const char*>("UTF8String");
        }
#endif
    };
}
