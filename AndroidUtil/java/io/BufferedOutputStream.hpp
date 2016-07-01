
#pragma once

#include "FilterOutputStream.hpp"

namespace java {
    namespace io {
        struct BufferedOutputStream:public FilterOutputStream{
            using FilterOutputStream::FilterOutputStream;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/io/BufferedOutputStream");
            
            static BufferedOutputStream create(const OutputStream &out){
                return std::move(java::lang::Object::create<BufferedOutputStream>(out));
            }
#endif
        };
    }
}
