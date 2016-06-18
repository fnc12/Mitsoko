
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        
        /**
         *  S must be java::lang::String. Template used to solve two headers include each other problem.
         */
        template<class S>
        struct _CharSequence:public Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/lang/CharSequence");
#ifdef __ANDROID__
            S toString(){
                return this->sendMessage<S>("toString");
            }
#endif
        };
    }
}
