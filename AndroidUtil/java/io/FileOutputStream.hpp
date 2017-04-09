
#ifndef __VIPER__ANDROID_UTIL__JAVA__IO__FILE_OUTPUT_STREAM__
#define __VIPER__ANDROID_UTIL__JAVA__IO__FILE_OUTPUT_STREAM__

#include "OutputStream.hpp"
#include "File.hpp"

namespace java {
    
    namespace io {
        
        struct FileOutputStream : public OutputStream {
            
            using OutputStream::OutputStream;
            
#ifdef __ANDROID__

            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/io/FileOutputStream");
            
            static FileOutputStream create(const File &file);
            
#endif  //__ANDROID__
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__IO__FILE_OUTPUT_STREAM__
