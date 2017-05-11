//
//  UrlResponse.cpp
//  Groozim
//
//  Created by John Zakharov on 21.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Response.hpp"

#include "Mitsoko/AndroidUtil/java/lang/String.hpp"

Mitsoko::Url::Response::Response(decltype(response) response_):response(response_),headers{*this}{}

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

std::string Mitsoko::Url::Response::Headers::operator[](const std::string &key) {
#ifdef __APPLE__
    auto nsKey = NS::String::stringWithCString(key.c_str(), NS::String::Encoding::UTF8);
    auto headersDict = response.response.allHeaderFields();
    if(auto value = headersDict[nsKey].as<NS::String>()){
        return value.UTF8String();
    }else{
        return {};
    }
#else
    using namespace java::lang;
    using namespace java::util;
    auto javaKey = String::create(key);
    auto headersMap = response.response.sendMessage<Map<String, List<String>>>("getHeaders");
    if(auto resList = headersMap.get(javaKey)){
        if(resList.size()){
            if(auto res = resList.get(0)){
                return res.c_str();
            }else{
                return {};
            }
        }else{
            return {};
        }
    }else{
        return {};
    }
#endif
}
