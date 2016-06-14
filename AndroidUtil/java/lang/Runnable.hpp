
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        struct Runnable:public Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/lang/Runnable");
        };
    }
}
