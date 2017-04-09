
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__BASE_ADAPTER__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__BASE_ADAPTER__

#include "ListAdapter.hpp"

namespace android{
    
    namespace widget{
        
        struct BaseAdapter : public ListAdapter{
            
            using ListAdapter::ListAdapter;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/widget/BaseAdapter");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__BASE_ADAPTER__
