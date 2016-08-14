//
//  Bundle.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Bundle.hpp"

#ifdef __APPLE__

const std::string NS::Bundle::className="NSBundle";

NS::Bundle NS::Bundle::mainBundle(){
    auto cls=NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls, "mainBundle");
}

NS::Array NS::Bundle::preferredLocalizations(){
    return this->sendMessage<Handle>("preferredLocalizations");
}

#endif  //__APPLE__
