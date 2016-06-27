
#pragma once

#include "FrameLayout.hpp"

namespace android{
    namespace widget{
        struct HorizontalScrollView:public FrameLayout{
            using FrameLayout::FrameLayout;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/HorizontalScrollView");
            
#endif
        };
    }
}
