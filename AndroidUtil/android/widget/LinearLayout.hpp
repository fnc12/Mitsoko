
#pragma once

#include "Viper/AndroidUtil/android/view/ViewGroup.hpp"

namespace android{
    namespace widget{
        struct LinearLayout:public android::view::ViewGroup{
            using ViewGroup::ViewGroup;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/LinearLayout");
            
            struct LayoutParams:public android::view::ViewGroup::MarginLayoutParams{
                using MarginLayoutParams::MarginLayoutParams;
                STATIC_VAR(const std::string, signature, "android/widget/LinearLayout$LayoutParams");
                
                static LayoutParams create(int width, int height){
                    return java::lang::Object::create<LayoutParams>(width,height);
                }
            };
#endif
        };
    }
}
