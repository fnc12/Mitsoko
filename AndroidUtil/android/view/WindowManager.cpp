//
//  WindowManager.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "WindowManager.hpp"

#ifdef __ANDROID__

//const std::string android::view::WindowManager::signature="android/view/WindowManager";

//const std::string android::view::WindowManager::LayoutParams::signature="android/view/WindowManager$LayoutParams";

int android::view::WindowManager::LayoutParams::SOFT_INPUT_STATE_VISIBLE(){
    if(java::lang::Class cls=java::lang::Class::find<WindowManager::LayoutParams>()){
        return cls.getStaticField<int>("SOFT_INPUT_STATE_VISIBLE");
    }else{
        return -1;
    }
}

#endif  //__ANDROID__
