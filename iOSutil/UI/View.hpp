
#pragma once

#include "Responder.hpp"

namespace UI {
    struct View:public UI::Responder{
        using Responder::Responder;
#ifdef __APPLE__
        void setHidden(bool newValue){
            this->sendMessage<void>("setHidden:", newValue);
        }
#endif
    };
}
