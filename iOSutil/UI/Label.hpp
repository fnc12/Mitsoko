
#pragma once

#include "View.hpp"

namespace UI {
    struct Label:public UI::View{
        using View::View;
#ifdef __APPLE__
        void setText(const std::string &newValue){
            auto str=CF::String::create(newValue);
            this->sendMessage<void>("setText:", str.handle);
        }
#endif
    };
}
