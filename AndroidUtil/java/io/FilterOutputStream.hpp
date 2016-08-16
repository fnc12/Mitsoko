
#ifndef __VIPER__ANDROID_UTIL__JAVA__IO__FILTER_OUTPUT_STREAM__
#define __VIPER__ANDROID_UTIL__JAVA__IO__FILTER_OUTPUT_STREAM__

#include "OutputStream.hpp"

namespace java {
    
    namespace io {
        
        struct FilterOutputStream:public OutputStream{
            
            using OutputStream::OutputStream;
            
#ifdef __ANDROID__
            
//            static const std::string signature;
            STATIC_VAR(const std::string, signature, "java/io/FilterOutputStream");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__IO__FILTER_OUTPUT_STREAM__
