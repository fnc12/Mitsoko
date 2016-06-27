
#pragma once

#include "View.hpp"

namespace UI {
    struct ScrollView:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIScrollView");
        
        
#endif
    };
}
