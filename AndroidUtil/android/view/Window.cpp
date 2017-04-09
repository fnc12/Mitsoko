//
//  Window.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Window.hpp"

#ifdef __ANDROID__

const std::string android::view::Window::signature = "android/view/Window";

void android::view::Window::setSoftInputMode(int mode){
    this->sendMessage<void>("setSoftInputMode",mode);
}

#endif  //__ANDROID__
