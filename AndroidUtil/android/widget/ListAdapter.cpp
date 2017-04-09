//
//  ListAdapter.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ListAdapter.hpp"

#ifdef __ANDROID__

const std::string android::widget::ListAdapter::signature = "android/widget/ListAdapter";

void android::widget::ListAdapter::notifyDataSetChanged(){
    this->sendMessage<void>("notifyDataSetChanged");
}

#endif  //__ANDROID__
