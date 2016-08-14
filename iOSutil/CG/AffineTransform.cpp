//
//  AffineTransform.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "AffineTransform.hpp"

#ifdef __APPLE__

CG::AffineTransform::AffineTransform(CGAffineTransform s):CGAffineTransform(s){}

/*CG::AffineTransform& CG::AffineTransform::operator=(const CGAffineTransform &other){
    this->CGAffineTransform::operator=(other);
    return *this;
}*/

CG::AffineTransform CG::AffineTransform::makeScale(CG::Float sx,CG::Float sy){
    /*CG::AffineTransform res(CGAffineTransformMakeScale(sx, sy));
    auto t=CGAffineTransformMakeScale(sx, sy);
    res=t;
    return res;*/
    return CGAffineTransformMakeScale(sx, sy);
}

#endif
