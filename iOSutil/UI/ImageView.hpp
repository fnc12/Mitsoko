
#pragma once

#include "View.hpp"
#include "Image.hpp"

namespace UI {
    struct ImageView:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(std::string, className, "UIImageView");
        
        void setImage(const UI::Image &newValue){
            this->sendMessage<void>("setImage:", newValue.handle);
        }
        
        UI::Image image(){
            return this->sendMessage<Handle>("image");
        }
#endif
    };
}
