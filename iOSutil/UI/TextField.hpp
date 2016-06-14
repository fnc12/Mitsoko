
#pragma once

#include "Control.hpp"

namespace UI {
    struct TextField:public UI::Control{
        using Control::Control;
#ifdef __APPLE__
        std::string text(){
            auto t=this->sendMessage<NSString*>("text");
            if(t){
                return t.UTF8String;
            }else{
                return {};
            }
        }
#endif
    };
}
