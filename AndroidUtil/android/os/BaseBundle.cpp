//
//  BaseBundle.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "BaseBundle.hpp"

#ifdef __ANDROID__

//const std::string android::os::BaseBundle::signature="android/os/BaseBundle";

java::lang::Object android::os::BaseBundle::get(const char *key){
    return std::move(this->get(std::string(key)));
}

java::lang::Object android::os::BaseBundle::get(const std::string &key){
    auto s=java::lang::String::create(key);
    return std::move(this->get(s));
}

java::lang::Object android::os::BaseBundle::get(const java::lang::String &key){
    return this->sendMessage<java::lang::Object>("get",key);
}

#endif  //__ANDROID__
