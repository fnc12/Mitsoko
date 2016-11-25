//
//  MutableURLRequest.cpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "MutableURLRequest.hpp"
#include <iostream>

using std::cout;
using std::endl;

#ifdef __APPLE__

const std::string NS::MutableURLRequest::className = "NSMutableURLRequest";

NS::MutableURLRequest NS::MutableURLRequest::create() {
    return Object::create<NS::MutableURLRequest>(className);
}

void NS::MutableURLRequest::setURL(const NS::URL &newValue) {
    this->sendMessage<void>("setURL:", newValue.handle);
}

void NS::MutableURLRequest::setHTTPMethod(const NS::String &newValue) {
    this->sendMessage<void>("setHTTPMethod:", newValue.handle);
}

void NS::MutableURLRequest::setHTTPMethod(const char *newValue) {
    this->setHTTPMethod(std::string(newValue));
}

void NS::MutableURLRequest::setHTTPBody(const NS::Data &newValue) {
    this->sendMessage<void>("setHTTPBody:", newValue.handle);
}

void NS::MutableURLRequest::setHTTPMethod(const std::string &newValue) {
    auto n = NS::String::stringWithCString(newValue.c_str(), NS::String::Encoding::UTF8);
//    cout<<"n = "<<n.UTF8String()<<endl;
    this->setHTTPMethod(n);
}

void NS::MutableURLRequest::setValueForHTTPHeaderField(const NS::String &value, const NS::String &field) {
    this->sendMessage<void>("setValue:forHTTPHeaderField:", value.handle, field.handle);
}

void NS::MutableURLRequest::setValueForHTTPHeaderField(const std::string &value,const std::string &field) {
    auto v = NS::String::stringWithCString(value.c_str(), NS::String::Encoding::UTF8);
    auto f = NS::String::stringWithCString(field.c_str(), NS::String::Encoding::UTF8);
    this->setValueForHTTPHeaderField(v, f);
}

#endif  //__APPLE__
