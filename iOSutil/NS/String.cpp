//
//  String.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "String.hpp"
#include <iostream>
#include "Viper/iOSutil/CF/String.hpp"

using std::cout;
using std::endl;

#ifdef __APPLE__

const std::string NS::String::className = "NSString";

const char* NS::String::UTF8String(){
    return this->sendMessage<const char*>("UTF8String");
}

NS::Data NS::String::dataUsingEncoding(Encoding encoding) {
    return this->sendMessage<Handle>("dataUsingEncoding:", NSStringEncoding(encoding));
}

NS::String NS::String::stringWithCString(const char *cStr, NS::String::Encoding encoding) {
    auto cls = NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls, "stringWithCString:encoding:", cStr, NSStringEncoding(encoding));
}

NS::String NS::String::create(const NS::Data &data, NS::String::Encoding encoding) {
    /*auto cls = NS::getClass(className);
    assert(cls);
    auto handle = sendMessage<Handle>(cls, "alloc");
    NS::String res(handle);
    res.initWithData(data, encoding);
    return std::move(res);*/
    return (__bridge Handle)[[NSString alloc] initWithData:(__bridge id)data.handle encoding:(NSStringEncoding)encoding];
}

void NS::String::initWithData(const NS::Data &data, NS::String::Encoding encoding) {
    this->sendMessage<Handle>("initWithData:encoding:", data.handle, NSStringEncoding(encoding));
}

/*NS::String NS::String::create(const std::string &str) {
    NS::String res;
    {
        auto s = CF::String::create(str);
//        cout<<"s.retainCount() = "<<s.retainCount()<<endl;
        res = NS::String(s.handle);
//        cout<<"s.retainCount() = "<<s.retainCount()<<endl;
//        cout<<"res.retainCount() = "<<res.retainCount()<<endl;
    }
//    cout<<"res.retainCount() = "<<res.retainCount()<<endl;
//    auto retCount = res.retainCount();
//    assert(retCount == 1);
    return res;
}*/

#endif  //__APPLE__
