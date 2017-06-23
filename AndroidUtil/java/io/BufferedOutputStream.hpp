
#ifndef __VIPER__ANDROID_UTIL__JAVA__IOS__BUFFERED_OUTPUT_STREAM__
#define __VIPER__ANDROID_UTIL__JAVA__IOS__BUFFERED_OUTPUT_STREAM__

#include "FilterOutputStream.hpp"

namespace java {
    
    namespace io {
        
        struct BufferedOutputStream : public FilterOutputStream {
            
            using FilterOutputStream::FilterOutputStream;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            static BufferedOutputStream create(const OutputStream &out);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__IOS__BUFFERED_OUTPUT_STREAM__
