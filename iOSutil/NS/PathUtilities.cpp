//
//  PathUtilities.cpp
//  GoZebra
//
//  Created by John Zakharov on 02.04.17.
//  Copyright © 2017 Outlaw Studio. All rights reserved.
//

#include "PathUtilities.hpp"

#ifdef __APPLE__

#import <Foundation/NSPathUtilities.h>

std::string NS::TemporaryDirectory() {
    auto res = NSTemporaryDirectory().UTF8String;
    if(res){
        return res;
    }else{
        return {};
    }
}

#endif
