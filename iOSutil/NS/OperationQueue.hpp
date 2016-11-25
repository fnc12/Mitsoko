//
//  OperationQueue.hpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef OperationQueue_hpp
#define OperationQueue_hpp

#include "Object.hpp"

namespace NS {
    
    struct OperationQueue : public NS::Object {
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        static NS::OperationQueue mainQueue();
        
#endif  //__APPLE__
    };
}

#endif /* OperationQueue_hpp */
