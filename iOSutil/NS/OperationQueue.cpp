//
//  OperationQueue.cpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "OperationQueue.hpp"

#ifdef __APPLE__

const std::string NS::OperationQueue::className = "NSOperationQueue";

NS::OperationQueue NS::OperationQueue::mainQueue() {
    auto cls = NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls, "mainQueue");
}

#endif  //__APPLE__
