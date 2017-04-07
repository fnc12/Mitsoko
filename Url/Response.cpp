//
//  UrlResponse.cpp
//  Groozim
//
//  Created by John Zakharov on 21.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Response.hpp"

#include "Mitsoko/AndroidUtil/java/lang/String.hpp"

Mitsoko::Url::Response::Response(decltype(response) response_):response(response_){}

int Mitsoko::Url::Response::statusCode() {
    
#ifdef __APPLE__
    return response.statusCode();
#else
    return response.sendMessage<int>("getStatusCode");
#endif  //__APPLE__
    
}

std::string Mitsoko::Url::Response::statusDescription() {
    
#ifdef __APPLE__
    if(auto res = NS::HTTPURLResponse::localizedStringForStatusCode(this->statusCode())){
        return res.UTF8String();
    }else{
        return {};
    }
#else
    if(auto res = response.sendMessage<java::lang::String>("getStatusDescription")){
        return res.c_str();
    }else{
        return {};
    }
#endif  //__APPLE__
    
}

Mitsoko::Url::Response::operator bool() const {
    return bool(response);
}
