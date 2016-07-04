
#pragma once

#include "Control.hpp"

namespace UI {
    struct PageControl:public UI::Control{
        using Control::Control;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIPageControl");
        
        void setNumberOfPages(int newValue){
            this->sendMessage<void>("setNumberOfPages:", NSInteger(newValue));
        }
        
        int numberOfPages(){
            return int(this->sendMessage<NSInteger>("numberOfPages"));
        }
#endif
    };
}
