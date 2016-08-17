//
//  Fragment.cpp
//  Groozim
//
//  Created by John Zakharov on 16.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Fragment.hpp"

#ifdef __ANDROID__

//const std::string java::app::Fragment::signature="android/app/Fragment";

auto android::app::Fragment::getActivity()->Activity{
    return this->sendMessage<Activity>("getActivity");
}

#endif  //__ANDROID__
