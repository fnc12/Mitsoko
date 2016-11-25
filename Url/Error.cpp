//
//  Error.cpp
//  Groozim
//
//  Created by John Zakharov on 22.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Error.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"

Viper::Url::Error::Error(decltype(error) error_):error(error_){}

int Viper::Url::Error::code() {
    
#ifdef __APPLE__
    return error.code();
#else
    return error.sendMessage<int>("getCode");
#endif  //__APPLE__
    
}

std::string Viper::Url::Error::message() {
    
#ifdef __APPLE__
    return error.localizedDescription();
#else
    if(auto res = error.sendMessage<java::lang::String>("getText")){
        return res.c_str();
    }else{
        return {};
    }
#endif  //__APPLE__
    
}

Viper::Url::Error::operator bool() const {
    return bool(error);
}
