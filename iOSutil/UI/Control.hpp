
#pragma once

#include "View.hpp"

namespace UI {
    struct Control:public UI::View{
        using View::View;
#ifdef __APPLE__
        void setEnabled(bool newValue){
            this->sendMessage<void>("setEnabled:",newValue);
        }
        
        bool enabled(){
            return this->sendMessage<bool>("isEnabled");
        }
#endif
    };
}
