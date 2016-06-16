
#pragma once

#include "View.hpp"

namespace UI {
    struct Image:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(std::string, className, "UIImage");
        
        static UI::Image create(const std::string &named){
            auto cls=NS::getClass(className());
            auto str=CF::String::create(named);
            return NS::Object::sendMessage<Handle>(cls,"imageNamed:", str.handle);
        }
#endif
    };
}
