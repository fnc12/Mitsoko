
#pragma once

#include "Adapter.hpp"

namespace android{
    namespace widget{
        struct ListAdapter:public Adapter{
            using Adapter::Adapter;
            STATIC_VAR(const std::string, signature, "android/widget/ListAdapter");
#ifdef __ANDROID__
            void notifyDataSetChanged(){
                this->sendMessage<void>("notifyDataSetChanged");
            }
#endif
        };
    }
}
