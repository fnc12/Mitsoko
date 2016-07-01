
#pragma once

#include "OutputStream.hpp"
#include "File.hpp"

namespace java {
    namespace io {
        struct FileOutputStream:public OutputStream{
            using OutputStream::OutputStream;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/io/FileOutputStream");
            
            static FileOutputStream create(const File &file){
                return java::lang::Object::create<FileOutputStream>(file);
            }
#endif
        };
    }
}
