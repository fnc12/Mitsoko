
#pragma once

#include "View.hpp"
#include "Viper/iOSutil/CG/Size.hpp"

namespace UI {
    struct ScrollView:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIScrollView");
        
        void setContentSize(const CG::Size &newValue){
            this->sendMessage<void>("setContentSize:", CGSize(newValue));
        }
        
        CG::Size contentSize(){
            return this->sendMessage<CGSize>("contentSize");
        }
#endif
    };
}
