//
//  URLRequest.hpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef URLRequest_hpp
#define URLRequest_hpp

#include "Object.hpp"
#include "URL.hpp"
#include "String.hpp"

namespace NS {
    
    struct URLRequest : public NS::Object {
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        NS::URL URL();
        
        NS::String HTTPMethod();
        
#endif
    };
}

#endif /* URLRequest_hpp */
