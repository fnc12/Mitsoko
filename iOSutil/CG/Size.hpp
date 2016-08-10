
#ifndef __VIPER__IOS_UTIL__CG__SIZE__
#define __VIPER__IOS_UTIL__CG__SIZE__

#ifdef __APPLE__

#include "CG.hpp"

namespace CG {
    struct Size:public CGSize{
        
        Size();
        
        Size(CGSize s);
        
        Size(decltype(width) w,decltype(height) h);
    };
}
#endif

#endif  //__VIPER__IOS_UTIL__CG__SIZE__
