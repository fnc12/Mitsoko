//
//  TextAttachment.hpp
//  Groozim
//
//  Created by John Zakharov on 05.09.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef __VIPER__IOS_UTIL__NS__TEXT_ATTACHMENT__
#define __VIPER__IOS_UTIL__NS__TEXT_ATTACHMENT__

#include "Object.hpp"

namespace NS {
    
    struct TextAttachment:public NS::Object{
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
#endif  //__APPLE__
    };
}

#endif  //__VIPER__IOS_UTIL__NS__TEXT_ATTACHMENT__
