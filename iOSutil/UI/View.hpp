
#pragma once

#include "Responder.hpp"
#include "Viper/iOSutil/CG/AffineTransform.hpp"

namespace UI {
    struct View:public UI::Responder{
        using Responder::Responder;
#ifdef __APPLE__
        void setHidden(bool newValue){
            this->sendMessage<void>("setHidden:", newValue);
        }
        
        void setTransform(const CG::AffineTransform &newValue){
            this->sendMessage<void>("setTransform:", newValue);
        }
        
        CG::AffineTransform transform(){
            return this->sendMessage<CG::AffineTransform>("transform");
        }
#endif
    };
}
