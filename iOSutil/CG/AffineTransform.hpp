
#ifndef __VIPER__IOS_UTIL__CG__AFFINE_TRANSFORM__
#define __VIPER__IOS_UTIL__CG__AFFINE_TRANSFORM__

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct AffineTransform:public CGAffineTransform{
        
        AffineTransform& operator=(const CGAffineTransform &other);
        
        static CG::AffineTransform makeScale(CG::Float sx,CG::Float sy);
    };
}
#endif

#endif  //__VIPER__IOS_UTIL__CG__AFFINE_TRANSFORM__
