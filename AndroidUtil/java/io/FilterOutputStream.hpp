
#pragma once

#include "OutputStream.hpp"

namespace java {
    namespace io {
        struct FilterOutputStream:public OutputStream{
            using OutputStream::OutputStream;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/io/FilterOutputStream");
#endif
        };
    }
}
