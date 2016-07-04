
#pragma once

#ifdef __APPLE__

#include "CG.hpp"
#include "Point.hpp"
#include "Size.hpp"

namespace CG {
    struct Rect:public CGRect{
        Rect():Rect(CG::Point(),CG::Size()){}
        
        Rect(CGRect r):CGRect(r){}
        
        Rect(const CG::Point &o,const CG::Size &s){
            this->origin=CGPoint(o);
            this->size=CGSize(s);
        }
        
        CG::Float width() const{
            return this->size.width;
        }
        
        CG::Float height() const{
            return this->size.height;
        }
        
    };
}
#endif
