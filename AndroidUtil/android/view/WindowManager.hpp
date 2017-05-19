
#ifndef __VIPER__ANDROID_UTIL__ANDROID__VIEW__WINDOW_MANAGER__
#define __VIPER__ANDROID_UTIL__ANDROID__VIEW__WINDOW_MANAGER__

#include "ViewManager.hpp"
#include "ViewGroup.hpp"

namespace android{
    
    namespace view{
        
        struct WindowManager : public java::lang::Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            struct LayoutParams : public ViewGroup::LayoutParams {
                
                typedef ViewGroup::LayoutParams Super;
                
                using Super::Super;
                
                static const std::string signature;
                
                static int SOFT_INPUT_STATE_VISIBLE();
            };
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__VIEW__WINDOW_MANAGER__
