//
//  Dialog.cpp
//  Groozim
//
//  Created by John Zakharov on 16.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Dialog.hpp"

#ifdef __ANDROID__

//const std::string java::app::Dialog::signature="android/app/Dialog";

auto java::app::Dialog::getWindow()->view::Window{
    return this->sendMessage<view::Window>("getWindow");
}

#endif  //__ANDROID__
