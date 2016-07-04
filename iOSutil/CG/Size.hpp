
#pragma once

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct Size:public CGSize{
        
        Size():Size(0,0){}
        
        Size(CGSize s):CGSize(s){}
        
        Size(decltype(width) w,decltype(height) h){
            this->width=w;
            this->height=h;
        }
    };
}
#endif
