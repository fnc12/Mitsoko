
#pragma once

#include "AdapterView.hpp"

namespace android{
    namespace widget{
        struct AbsListView:public AdapterView{
            using AdapterView::AdapterView;
            STATIC_VAR(const std::string, signature, "android/widget/AbsListView");
        };
    }
}
