//
//  AppCompatActivity.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "AppCompatActivity.hpp"

#ifdef __ANDROID__

//const std::string android::support::v7::app::AppCompatActivity::signature="android/support/v7/app/AppCompatActivity";

auto android::support::v7::app::AppCompatActivity::getSupportActionBar()->ActionBar{
    return this->sendMessage<ActionBar>("getSupportActionBar");
}

void android::support::v7::app::AppCompatActivity::invalidateOptionsMenu(){
    this->sendMessage<void>("invalidateOptionsMenu");
}

#endif  //__ANDROID__
