
#pragma once

#include "Control.hpp"

namespace UI {
    struct RefreshControl:public UI::Control{
        using Control::Control;
#ifdef __APPLE__
        void endRefreshing(){
            this->sendMessage<void>(this->handle, "endRefreshing");
        }
#endif
    };
}
