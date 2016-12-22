//
//  URL.cpp
//  Groozim
//
//  Created by John Zakharov on 29.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "URL.hpp"

#ifdef __APPLE__

const std::string NS::URL::className = "NSURL";

NS::URL NS::URL::create(const std::string &str){
    auto cls = NS::getClass(className);
    assert(cls);
    auto cfString = CF::String::create(str);
    NS::URL res = sendMessage<Handle>(cls, "alloc");
    res.initWithString(cfString);
    return res;
}

void NS::URL::initWithString(const CF::String &str){
    this->handle = this->sendMessage<Handle>("initWithString:", str.handle);
}

std::string NS::URL::absoluteString() {
    if(NS::String res = this->sendMessage<Handle>("absoluteString")){
        return res.UTF8String();
    }else{
        return {};
    }
}

#endif  //__APPLE__
