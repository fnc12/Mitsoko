
#pragma once

#include "Control.hpp"
#include "TextInput.hpp"

namespace UI {
    struct TextField:public virtual UI::Control, public virtual UI::TextInput{
        
        TextField():
        UI::Control(),
        UI::TextInput(){}
        
        TextField(Handle handle):
        UI::Control(handle),
        UI::TextInput(handle){}
        
        typedef UI::Control Super;
#ifdef __APPLE__
        void setText(const std::string &newValue){
            auto s=CF::String::create(newValue);
            this->setText(s);
        }
        
        void setText(const CF::String &newValue){
            this->Super::sendMessage<void>("setText:", newValue.handle);
        }
        
        std::string text(){
            auto t=this->Super::sendMessage<NSString*>("text");
            if(t){
                return t.UTF8String;
            }else{
                return {};
            }
        }
#endif
    };
}
