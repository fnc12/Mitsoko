//
//  Context.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Context.hpp"

#ifdef __ANDROID__

//const std::string android::content::Context::signature="android/content/Context";

auto android::content::Context::getResources()->res::Resources{
    return this->sendMessage<res::Resources>("getResources");
}

auto android::content::Context::getPackageName()->java::lang::String{
    return this->sendMessage<java::lang::String>("getPackageName");
}

#endif  //__ANDROID__
