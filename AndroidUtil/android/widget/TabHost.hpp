
#pragma once

#include "FrameLayout.hpp"

namespace android{
    namespace widget{
        struct TabHost:public FrameLayout{
            using FrameLayout::FrameLayout;
            STATIC_VAR(const std::string, signature, "android/widget/TabHost");
#ifdef __ANDROID__
            int getCurrentTab(){
                return this->sendMessage<jint>("getCurrentTab");
            }
#endif
        };
    }
}
