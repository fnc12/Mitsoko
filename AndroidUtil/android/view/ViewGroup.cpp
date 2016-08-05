//
//  ViewGroup.cpp
//  Jako
//
//  Created by John Zakharov on 05.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ViewGroup.hpp"

#ifdef __ANDROID__

template<>
void android::view::View::setLayoutParams<android::view::ViewGroup::LayoutParams>(const android::view::ViewGroup::LayoutParams &params){
    this->sendMessage<void>("setLayoutParams",params);
}

#endif
