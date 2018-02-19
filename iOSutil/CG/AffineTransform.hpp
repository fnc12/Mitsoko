
#ifndef __MITSOKO__IOS_UTIL__CG__AFFINE_TRANSFORM__
#define __MITSOKO__IOS_UTIL__CG__AFFINE_TRANSFORM__

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    
    struct AffineTransform : public CGAffineTransform {
        AffineTransform(CGAffineTransform s);
        
        static CG::AffineTransform makeScale(CG::Float sx, CG::Float sy);
        
        static CG::AffineTransform makeRotation(CG::Float angle);
        
        static CG::AffineTransform identity;
    };
}
#endif

#endif  //__MITSOKO__IOS_UTIL__CG__AFFINE_TRANSFORM__
