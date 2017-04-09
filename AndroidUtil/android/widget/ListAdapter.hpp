
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__LIST_ADAPTER__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__LIST_ADAPTER__

#include "Adapter.hpp"

namespace android{
    
    namespace widget{
        
        struct ListAdapter:public Adapter{
            
            using Adapter::Adapter;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/widget/ListAdapter");
            
            void notifyDataSetChanged();
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__LIST_ADAPTER__
