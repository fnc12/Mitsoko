
#ifndef __VIPER__ANDROID_UTIL__ANDROID__VIEW__WINDOW_MANAGER__
#define __VIPER__ANDROID_UTIL__ANDROID__VIEW__WINDOW_MANAGER__

#include "ViewManager.hpp"
#include "ViewGroup.hpp"

namespace android{
    
    namespace view{
        
        struct WindowManager:public java::lang::Object{
            
            using Object::Object;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/view/WindowManager");
            
            struct LayoutParams:public ViewGroup::LayoutParams{
                
                typedef ViewGroup::LayoutParams Super;
                
                using Super::Super;
                
//            const std::string signature;
                STATIC_VAR(const std::string, signature, "android/view/WindowManager$LayoutParams");
                
                static int SOFT_INPUT_STATE_VISIBLE();
            };
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__VIEW__WINDOW_MANAGER__
