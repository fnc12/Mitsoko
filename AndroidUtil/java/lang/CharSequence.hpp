
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        struct CharSequence:public Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/lang/CharSequence");
#ifdef __ANDROID__
            String toString(){
                return this->sendMessage<String>("toString");
            }
#endif
        };
    }
}
