//
//  HTTPURLResponse.cpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "HTTPURLResponse.hpp"

#ifdef __APPLE__

const std::string NS::HTTPURLResponse::className = "NSHTTPURLResponse";

int NS::HTTPURLResponse::statusCode() {
//    return int(this->sendMessage<NSInteger>("statusCode"));
    auto res = ((__bridge NSHTTPURLResponse*)this->handle).statusCode;
    return (int)res;
}

NS::String NS::HTTPURLResponse::localizedStringForStatusCode(int statusCode) {
    auto cls = NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls, "localizedStringForStatusCode:", NSInteger(statusCode));
}

NS::Dictionary NS::HTTPURLResponse::allHeaderFields() {
//    return this->sendMessage<Handle>("allHeaderFields");
    auto headers = ((__bridge NSHTTPURLResponse*)this->handle).allHeaderFields;
    return (__bridge Handle)headers;
}

#endif  //__APPLE__
