//
//  TabHost.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TabHost.hpp"

#ifdef __ANDROID__

const std::string android::widget::TabHost::signature = "android/widget/TabHost";

int android::widget::TabHost::getCurrentTab(){
    return this->sendMessage<int>("getCurrentTab");
}

#endif  //__ANDROID__
