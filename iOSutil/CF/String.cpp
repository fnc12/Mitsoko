//
//  String.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "String.hpp"

#ifdef __APPLE__

CF::String CF::String::create(std::experimental::optional<std::string> str){
    if(str){
        return std::move(create(*str));
    }else{
        return {};
    }
}

CF::String CF::String::create(const std::string &str){
    return std::move(create(str.c_str()));
}

CF::String CF::String::create(const char *cString){
    auto cfStr=CFStringCreateWithCString(nullptr, cString, kCFStringEncodingUTF8);
    String res(cfStr);
    return std::move(res);
}

#endif  //__APPLE__
