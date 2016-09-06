//
//  Uri.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Uri.hpp"

#ifdef __ANDROID__

//const std::string android::net::Uri::signature="android/net/Uri";

auto android::net::Uri::parse(const std::string &uriString)->Uri{
//    LOGI("auto android::net::Uri::parse(const std::string &uriString)->Uri{");
    auto str=java::lang::String::create(uriString);
//    LOGI("auto str=java::lang::String::create(uriString);");
    return std::move(Uri::parse(str));
}

auto android::net::Uri::parse(const java::lang::String &uriString)->Uri{
//    LOGI("uriString = %s, %p",uriString.c_str(),uriString.handle);
    if(auto java_env=java::lang::JNI::Env()){
//        LOGI("if(auto java_env=java::lang::JNI::Env()){");
//        LOGI("java_env = %p",java_env);
        auto clazz = java_env->FindClass(signature().c_str());
//        LOGI("clazz = %p",clazz);
        auto methodSignature=generateMethodSignature<Uri,java::lang::String>();
//        LOGI("methodSignature = %s",methodSignature.c_str());
        auto mid=java_env->GetStaticMethodID(clazz,"parse",methodSignature.c_str());
//        LOGI("mid = %p",mid);
        return java_env->CallStaticObjectMethod(clazz,mid,(jobject)uriString.handle);
    }else{
        return {};
    }
}

#endif  //__ANDROID__
