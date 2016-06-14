
#pragma once

#include "Control.hpp"

namespace UI {
    
    struct Button:public UI::Control{
        using Control::Control;
#ifdef __APPLE__
        void setTitle(const std::string &title,UIControlState state){
            auto str=CF::String::create(title);
            this->sendMessage<void>("setTitle:forState:", str.handle,state);
        }
#endif
    };
}
