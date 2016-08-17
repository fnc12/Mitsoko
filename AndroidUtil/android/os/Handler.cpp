//
//  Handler.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Handler.hpp"

#ifdef __ANDROID__

//const std::string android::os::Handler::signature="android/os/Handler";

bool android::os::Handler::post(const java::lang::Runnable &runnable){
    return this->sendMessage<bool>("post",runnable);
}

auto android::os::Handler::create()->Handler{
    /*if(auto java_env=java::lang::JNI::Env()){
        if(auto clazz=java_env->FindClass(signature().c_str())){
            if(auto ctor = java_env->GetMethodID(clazz, "<init>", "()V")){
                return java_env->NewObject(clazz, ctor);
            }else{
                return nullptr;
            }
        }else{
            return nullptr;
        }
    }else{
        return nullptr;
    }*/
    return std::move(java::lang::Object::create<Handler>());
}

#endif  //__ANDROID__
