
#pragma once

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct Rect:public CGRect{
        
        CG::Float width() const{
            return this->size.width;
        }
        
        CG::Float height() const{
            return this->size.height;
        }
        
    };
}
#endif
