//
//  Point.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Point.hpp"

#ifdef __APPLE__

CG::Point::Point():Point(0,0){}

CG::Point::Point(CGPoint r):CGPoint(r){}

CG::Point::Point(decltype(x) x_,decltype(y) y_){
    this->x=x_;
    this->y=y_;
}

#endif
