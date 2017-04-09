//
//  Date.cpp
//  Groozim
//
//  Created by John Zakharov on 22.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Date.hpp"

#ifdef __ANDROID__

const std::string java::util::Date::signature = "java/util/Date";

//  TODO: replace with Object::create<Date>..
auto java::util::Date::create(long milliseconds)->Date{
    /*if(auto java_env=java::lang::JNI::Env()){
        if(auto clazz=java_env->FindClass(signature().c_str())){
            if(auto ctor = java_env->GetMethodID(clazz, "<init>", "(J)V")){
                return java_env->NewObject(clazz, ctor, jlong(milliseconds));
            }else{
                return {};
            }
        }else{
            return {};
        }
    }else{
        return {};
    }*/
    return java::lang::Object::create<Date>(milliseconds);
}

#endif  //__ANDROID__
