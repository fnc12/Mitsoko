
#pragma once

#include "Control.hpp"
#include "Viper/iOSutil/CF/String.hpp"
#include "Color.hpp"

namespace UI {
    struct SegmentedControl:public UI::Control{
        using Control::Control;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UISegmentedControl");
        
        void setTintColor(const UI::Color &newValue){
            this->sendMessage<void>("setTintColor:", newValue.handle);
        }
        
        UI::Color tintColor(){
            return this->sendMessage<Handle>("tintColor");
        }
        
        void setSelectedSegmentIndex(int newValue){
            this->sendMessage<void>("setSelectedSegmentIndex:", NSInteger(newValue));
        }
        
        int selectedSegmentIndex(){
            return int(this->sendMessage<NSInteger>("selectedSegmentIndex"));
        }
        
        void setTitle(const std::string &title,int segment){
            auto t=CF::String::create(title);
            this->setTitle(t, segment);
        }
        
        void setTitle(const CF::String &title,int segment){
            this->sendMessage<void>("setTitle:forSegmentAtIndex:", title.handle, NSUInteger(segment));
        }
        
        std::string titleForSegmentAtIndex(int segment){
            return this->sendMessage<NSString*>("titleForSegmentAtIndex:", NSUInteger(segment)).UTF8String;
        }
#endif
    };
}
