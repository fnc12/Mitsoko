//
//  TextWatcher.hpp
//  Groozim
//
//  Created by John Zakharov on 06.09.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef __VIPER__ANDROID_UTIL__ANDROID__TEXT__TEXT_WATCHER__
#define __VIPER__ANDROID_UTIL__ANDROID__TEXT__TEXT_WATCHER__

#include "NoCopySpan.hpp"

namespace android {
    
    namespace text {
        
        struct TextWatcher : public NoCopySpan{
            
            using NoCopySpan::NoCopySpan;
            
#ifdef __ANDROID__
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/text/TextWatcher");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif //__VIPER__ANDROID_UTIL__ANDROID__TEXT__TEXT_WATCHER__
