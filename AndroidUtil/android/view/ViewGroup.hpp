
#pragma once

#include "View.hpp"

namespace android{
    namespace view{
        struct ViewGroup:public View{
            using View::View;
            STATIC_VAR(const std::string, signature, "android/view/ViewGroup");
            
        };
    }
}
