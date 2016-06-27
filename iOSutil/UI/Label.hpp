
#pragma once

#include "View.hpp"
#include "Viper/iOSutil/UI/Color.hpp"

namespace UI {
    struct Label:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UILabel");
        
        void setText(const std::string &newValue){
            auto str=CF::String::create(newValue);
            this->sendMessage<void>("setText:", str.handle);
        }
        
        void setTextColor(const UI::Color &newValue){
            this->sendMessage<void>("setTextColor:", newValue.handle);
        }
        
        UI::Color textColor(){
            return this->sendMessage<Handle>("textColor");
        }
#endif
    };
}
