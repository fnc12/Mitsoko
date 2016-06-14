
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
    struct NavigationItem:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        void setTitle(const std::string &newValue){
            auto str=CF::String::create(newValue);
            this->sendMessage<void>("setTitle:", str.handle);
        }
        
        void setRightBarButtonItem(const UI::BarButtonItem &item){
            this->sendMessage<void>("setRightBarButtonItem:",item.handle);
        }
        
        UI::BarButtonItem rightBarButtonItem(){
            return this->sendMessage<Handle>("rightBarButtonItem");
        }
#endif
    };
}
