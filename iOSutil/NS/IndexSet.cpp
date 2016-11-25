//
//  IndexSet.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "IndexSet.hpp"

#ifdef __APPLE__

const std::string NS::IndexSet::className="NSIndexSet";

NS::IndexSet NS::IndexSet::create(int index){
    auto cls=NS::getClass(className);
    assert(cls);
    auto handle=sendMessage<Handle>(cls, "indexSetWithIndex:",NSUInteger(index));
    IndexSet res(handle);
    //            res.shouldClearOnDestroy=true;
    return res;
}

#endif  //__APPLE__
