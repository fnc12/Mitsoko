//
//  Date.hpp
//  mitsoko_ios
//
//  Created by John Zakharov on 25.11.2017.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#ifndef __Mitsoko__ios_util__ns_date__
#define __Mitsoko__ios_util__ns_date__

#include "Object.hpp"

#ifdef __APPLE__
#import <Foundation/NSDate.h>
#endif  //  __APPLE__

namespace NS {
    
#ifdef __APPLE__
    typedef NSTimeInterval TimeInterval;
#endif  //  __APPLE__
    
    struct Date : public NS::Object {
        using Object::Object;
#ifdef __APPLE__
        
        static const std::string className;
        
#endif  //  __APPLE__
    };
}

#endif /* __Mitsoko__ios_util__ns_date__ */
