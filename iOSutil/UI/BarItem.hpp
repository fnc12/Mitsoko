
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include "Image.hpp"
#include "Viper/iOSutil/CF/String.hpp"

namespace UI {
    struct BarItem:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        
        void setTag(int newValue){
            this->sendMessage<void>("setTag:", NSInteger(newValue));
        }
        
        int tag(){
            return int(this->sendMessage<NSInteger>("tag"));
        }
        
        void setImage(const UI::Image &newValue){
            this->sendMessage<void>("setImage:", newValue.handle);
        }
        
        UI::Image image(){
            return this->sendMessage<Handle>("image");
        }
        
        void setTitle(const std::string &newValue){
            auto s=CF::String::create(newValue);
            this->setTitle(s);
        }
        
        void setTitle(const CF::String &newValue){
            this->sendMessage<void>("setTitle:", newValue.handle);
        }
        
        std::string title(){
            NS::String res=this->sendMessage<Handle>("title");
            return res.UTF8String();
        }
        
        void setEnabled(bool newValue){
            this->sendMessage<void>("setEnabled:", newValue);
        }
#endif
    };
}
