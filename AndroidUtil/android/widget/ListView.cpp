//
//  ListView.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ListView.hpp"

#ifdef __ANDROID__

//const std::string android::widget::ListView::signature="android/widget/ListView";

auto android::widget::ListView::getAdapter()->ListAdapter{
    return this->sendMessage<ListAdapter>("getAdapter");
}

void android::widget::ListView::setAdapter(const ListAdapter &adapter){
    this->sendMessage<void>("setAdapter",adapter);
}

#endif  //__ANDROID__
