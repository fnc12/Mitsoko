
#ifndef __VIPER__IOS_UTIL__CG__RECT__
#define __VIPER__IOS_UTIL__CG__RECT__

#ifdef __APPLE__

#include "CG.hpp"
#include "Point.hpp"
#include "Size.hpp"

namespace CG {
    struct Rect:public CGRect{
        Rect();
        
        Rect(CGRect r);
        
        Rect(const CG::Point &o,const CG::Size &s);
        
        CG::Float width() const;
        
        CG::Float height() const;
        
    };
}
#endif

#endif  //__VIPER__IOS_UTIL__CG__RECT__
