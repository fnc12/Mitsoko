//
//  RelativeLayout.cpp
//  MyBusiness
//
//  Created by John Zakharov on 04.05.17.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#include "RelativeLayout.hpp"

#ifdef __ANDROID__

const std::string android::widget::RelativeLayout::signature = "android/widget/RelativeLayout";

const std::string android::widget::RelativeLayout::LayoutParams::signature = "android/widget/RelativeLayout$LayoutParams";

android::widget::RelativeLayout android::widget::RelativeLayout::create(const android::content::Context &context) {
    return java::lang::Object::create<RelativeLayout>(context);
}

#endif  //  __ANDROID__
