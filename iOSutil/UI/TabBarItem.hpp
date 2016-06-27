
#pragma once

#include "BarItem.hpp"
#include "Image.hpp"

namespace UI {
    struct TabBarItem:public UI::BarItem{
        using BarItem::BarItem;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UITabBarItem");
        
        void setSelectedImage(const UI::Image &newValue){
            this->sendMessage<void>("setSelectedImage:", newValue.handle);
        }
        
        UI::Image selectedImage(){
            return this->sendMessage<Handle>("selectedImage");
        }
#endif
    };
}
