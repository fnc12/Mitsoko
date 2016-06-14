
#pragma once

#include "ListAdapter.hpp"

namespace android{
    namespace widget{
        struct BaseAdapter:public ListAdapter{
            using ListAdapter::ListAdapter;
            STATIC_VAR(const std::string, signature, "android/widget/BaseAdapter");
        };
    }
}
