
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
    struct Responder:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        bool resignFirstResponder(){
            return this->sendMessage<bool>("resignFirstResponder");
        }
#endif
    };
}
