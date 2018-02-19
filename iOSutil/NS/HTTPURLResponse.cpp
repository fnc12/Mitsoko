
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
    auto headers = ((__bridge NSHTTPURLResponse*)this->handle).allHeaderFields;
    return (__bridge Handle)headers;
}

#endif  //__APPLE__
