
#pragma once

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct AffineTransform:public CGAffineTransform{
        
        AffineTransform& operator=(const CGAffineTransform &other){
            this->CGAffineTransform::operator=(other);
            return *this;
        }
        
        static CG::AffineTransform makeScale(CG::Float sx,CG::Float sy){
            CG::AffineTransform res;
            auto t=CGAffineTransformMakeScale(sx, sy);
            res=t;
            return res;
        }
    };
}
#endif
