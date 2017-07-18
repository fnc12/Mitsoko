//
//  UrlResponse.cpp
//  Groozim
//
//  Created by John Zakharov on 21.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Response.hpp"

#include "Mitsoko/AndroidUtil/java/lang/String.hpp"
#include "Mitsoko/AndroidUtil/java/lang/Class.hpp"
#include "Mitsoko/AndroidUtil/java/util/List.hpp"
#include "Mitsoko/AndroidUtil/java/util/Map.hpp"

Mitsoko::Url::Response::Response(decltype(response) response_):headers{*this}, response(response_){}

Mitsoko::Url::Response::Response(const Response& other):headers{*this}, response(other.response) {
    //..
}

Mitsoko::Url::Response::Response(Response &&other):headers{*this}, response(std::move(other.response)) {
    //..
}

int Mitsoko::Url::Response::statusCode() {
    
#ifdef __APPLE__
    return response.statusCode();
#else
    auto res = response.sendMessage<int>("getStatusCode");
    return res;
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
    LOGI("response.response = %p", response.response.handle);
    if(response){
        if(auto javaKey = String::create(key)){
            LOGI("javaKey = %p", javaKey.handle);
            if(auto res = response.response.sendMessage<String>("getHeaderField", javaKey)){
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
