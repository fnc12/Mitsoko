//
//  MutableArray.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "MutableArray.hpp"

#ifdef __APPLE__

const std::string NS::MutableArray::className="NSMutableArray";

NS::MutableArray NS::MutableArray::create(){
    auto cls=NS::getClass(className);
    assert(cls);
    auto handle=sendMessage<Handle>(cls, "new");
    NS::MutableArray res(handle);
    return res;
}

void NS::MutableArray::addObject(const NS::Object &anObject){
    this->sendMessage<void>("addObject:", anObject.handle);
}

#endif  //__APPLE__
