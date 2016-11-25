//
//  Range.hpp
//  Groozim
//
//  Created by John Zakharov on 05.09.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef __VIPER__IOS_UTIL__NS__RANGE__
#define __VIPER__IOS_UTIL__NS__RANGE__

#ifdef __APPLE__

#import <Foundation/Foundation.h>

namespace NS {
    
    struct Range:public NSRange{
        
        Range(const NSRange &s);
        
    };
}

#endif  //__APPLE__

#endif  //__VIPER__IOS_UTIL__NS__RANGE__
