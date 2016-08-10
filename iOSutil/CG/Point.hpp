
#ifndef __VIPER__IOS_UTIL__CG__POINT__
#define __VIPER__IOS_UTIL__CG__POINT__

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct Point:public CGPoint{
        
        Point();
        
        Point(CGPoint r);
        
        Point(decltype(x) x_,decltype(y) y_);
    };
}
#endif

#endif  //__VIPER__IOS_UTIL__CG__POINT__
