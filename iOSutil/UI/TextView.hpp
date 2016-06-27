
#pragma once

#include "ScrollView.hpp"

namespace UI {
    struct TextView:public UI::ScrollView{
        using ScrollView::ScrollView;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UITextView");
        
        void setText(const CF::String &newValue){
            this->sendMessage<void>("setText:", newValue.handle);
        }
        
        void setText(const std::string &newValue){
            auto t=CF::String::create(newValue);
            this->setText(t);
        }
        
        std::string text(){
            return this->sendMessage<NSString*>("text").UTF8String;
        }
#endif
    };
}
