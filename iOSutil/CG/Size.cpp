//
//  Size.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Size.hpp"

#ifdef __APPLE__

CG::Size::Size():Size(0,0){}

CG::Size::Size(CGSize s):CGSize(s){}

CG::Size::Size(decltype(width) w,decltype(height) h){
    this->width=w;
    this->height=h;
}

#endif
