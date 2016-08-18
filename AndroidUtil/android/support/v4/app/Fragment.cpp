//
//  Fragment.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Fragment.hpp"

#ifdef __ANDROID__

//const std::string android::support::v4::app::Fragment::signature="android/support/v4/app/Fragment";

auto android::support::v4::app::Fragment::getActivity()->FragmentActivity{
    return this->sendMessage<FragmentActivity>("getActivity");
}

void android::support::v4::app::Fragment::startActivityForResult(const android::content::Intent &intent,int requestCode){
    this->sendMessage<void>("startActivityForResult",intent,requestCode);
}

#endif  //__ANDROID__
