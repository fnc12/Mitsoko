
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace java {
    namespace io {
        struct OutputStream:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/io/OutputStream");
            
            void close(){
                this->sendMessage<void>("close");
            }
#endif
        };
    }
}
