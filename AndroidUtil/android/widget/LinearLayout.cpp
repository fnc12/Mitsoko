//
//  LinearLayout.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "LinearLayout.hpp"

#ifdef __ANDROID__

//const std::string android::widget::LinearLayout::signature="android/widget/LinearLayout";

//const std::string android::widget::LinearLayout::LayoutParams::signature="android/widget/LinearLayout$LayoutParams";

auto android::widget::LinearLayout::LayoutParams::create(int width, int height)->LayoutParams{
    return java::lang::Object::create<LayoutParams>(width,height);
}

#endif  //__ANDROID__
