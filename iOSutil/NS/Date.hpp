//
//  Date.hpp
//  mitsoko_ios
//
//  Created by John Zakharov on 20.11.2017.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#ifndef Date_hpp
#define Date_hpp

#include "Object.hpp"

namespace NS {
    
    struct Date : public NS::Object {
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
#endif  //  __APPLE__
    };
}

#endif /* Date_hpp */
