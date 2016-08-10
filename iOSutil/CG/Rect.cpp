//
//  Rect.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Rect.hpp"

#ifdef __APPLE__

CG::Rect::Rect():Rect(CG::Point(),CG::Size()){}

CG::Rect::Rect(CGRect r):CGRect(r){}

CG::Rect::Rect(const CG::Point &o,const CG::Size &s){
    this->origin=CGPoint(o);
    this->size=CGSize(s);
}

CG::Float CG::Rect::width() const{
    return this->size.width;
}

CG::Float CG::Rect::height() const{
    return this->size.height;
}

#endif
