#include "Error.hpp"
#include "String.hpp"

#ifdef __APPLE__

const std::string NS::Error::className = "NSError";

std::string NS::Error::domain() {
    NS::String s = this->sendMessage<Handle>("domain");
    return s.UTF8String();
}

int NS::Error::code() {
    return int(this->sendMessage<NSInteger>("code"));
}

NS::Dictionary NS::Error::userInfo() {
    return this->sendMessage<Handle>("userInfo");
}

std::string NS::Error::localizedDescription() {
    if(NS::String s = this->sendMessage<Handle>("localizedDescription")){
        return s.UTF8String();
    }else{
        return {};
    }
}

#endif  //__APPLE__
