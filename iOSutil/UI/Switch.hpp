
#pragma once

#include "Control.hpp"

namespace UI {
    struct Switch:public UI::Control{
        using Control::Control;
#ifdef __APPLE__
        void setOn(bool newValue){
            this->sendMessage<void>("setOn:",newValue);
        }
        bool on(){
            return this->sendMessage<bool>("isOn");
        }
#endif
    };
}
