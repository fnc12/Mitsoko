
#pragma once

#include "TextView.hpp"

namespace android{
    namespace widget{
        struct Button:public TextView{
            using TextView::TextView;
            STATIC_VAR(const std::string, signature, "android/widget/Button");
        };
    }
}
