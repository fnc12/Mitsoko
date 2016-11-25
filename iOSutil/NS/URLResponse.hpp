//
//  URLResponse.hpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef URLResponse_hpp
#define URLResponse_hpp

#include "Object.hpp"

namespace NS {
    struct URLResponse : public NS::Object {
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
#endif  //__APPLE__
    };
}

#endif /* URLResponse_hpp */
