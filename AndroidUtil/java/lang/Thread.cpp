//
//  Thread.cpp
//  Groozim
//
//  Created by John Zakharov on 16.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Thread.hpp"

#ifdef __ANDROID__

//const std::string java::lang::Thread::signature="java/lang/Thread";

void java::lang::Thread::start(){
    this->sendMessage<void>("start");
}

auto java::lang::Thread::create(const Runnable &runnable)->Thread{
    return java::lang::Object::create<Thread>(runnable);
}

#endif  //__ANDROID__
