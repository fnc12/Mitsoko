//
//  AffineTransform.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "AffineTransform.hpp"

#ifdef __APPLE__

CG::AffineTransform CG::AffineTransform::identity = CGAffineTransformIdentity;

CG::AffineTransform::AffineTransform(CGAffineTransform s): CGAffineTransform(s) {}

CG::AffineTransform CG::AffineTransform::makeScale(CG::Float sx, CG::Float sy) {
    return CGAffineTransformMakeScale(sx, sy);
}

CG::AffineTransform CG::AffineTransform::makeRotation(CG::Float angle) {
    return CGAffineTransformMakeRotation(angle);
}

#endif
