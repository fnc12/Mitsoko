
#pragma once

#include "Button.hpp"

namespace android{
    namespace widget{
        struct CompoundButton:public Button{
            using Button::Button;
            STATIC_VAR(const std::string, signature, "android/widget/CompoundButton");
#ifdef __ANDROID__
            void setChecked(bool newValue){
                this->sendMessage<void>("setChecked",newValue);
            }
            
            bool isChecked(){
                return this->sendMessage<bool>("isChecked");
            }
#endif
        };
    }
}
