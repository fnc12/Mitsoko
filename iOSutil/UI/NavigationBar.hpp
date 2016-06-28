
#pragma once

#include "View.hpp"
#include "Color.hpp"

namespace UI {
    struct NavigationBar:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UINavigationBar");
        
        void setBarTintColor(const UI::Color &newValue){
            this->sendMessage<void>("setBarTintColor:", newValue.handle);
        }
        
        UI::Color barTintColor(){
            return this->sendMessage<Handle>("barTintColor");
        }
        
        void setTintColor(const UI::Color &newValue){
            this->sendMessage<void>("setTintColor:", newValue.handle);
        }
        
        UI::Color tintColor(){
            return this->sendMessage<Handle>("tintColor");
        }
#endif
    };
}
