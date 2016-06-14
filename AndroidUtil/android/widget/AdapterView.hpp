
#pragma once

#include "Viper/AndroidUtil/android/view/ViewGroup.hpp"

namespace android{
    namespace widget{
        struct AdapterView:public view::ViewGroup{
            using ViewGroup::ViewGroup;
            STATIC_VAR(const std::string, signature, "android/widget/AdapterView");
        };
    }
}
