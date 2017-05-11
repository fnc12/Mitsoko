//
//  URLRequest.cpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "URLRequest.hpp"

#ifdef __APPLE__

const std::string NS::URLRequest::className = "NSURLRequest";

NS::URL NS::URLRequest::URL() {
    return this->sendMessage<Handle>("URL");
}

NS::String NS::URLRequest::HTTPMethod() {
    return this->sendMessage<Handle>("HTTPMethod");
}

NS::URLRequest NS::URLRequest::requestWithURL(const NS::URL &url) {
    auto cls = NS::getClass(className);
    assert(cls);
    return NS::Object::sendMessage<Handle>(cls, "requestWithURL:", url.handle);
}

#endif  //__APPLE__
