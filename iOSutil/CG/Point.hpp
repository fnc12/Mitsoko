
#pragma once

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct Point:public CGPoint{
        
        Point():Point(0,0){}
        
        Point(CGPoint r):CGPoint(r){}
        
        Point(decltype(x) x_,decltype(y) y_){
            this->x=x_;
            this->y=y_;
        }
    };
}
#endif
