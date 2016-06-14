
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
    struct BarItem:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        void setEnabled(bool newValue){
            this->sendMessage<void>("setEnabled:", newValue);
        }
#endif
    };
}
