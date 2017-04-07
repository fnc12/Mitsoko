//
//  View.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "View.hpp"

#include <iostream>

using std::cout;
using std::endl;

Mitsoko::ViewBase::~ViewBase(){
    
    //  unregister all table- or listview adapters hosted by this view..
    for(auto adapterId:this->adapterIds){
        TableListAdapter::registerAdapter(adapterId, {});
    }
    this->adapterIds.clear();
}

void Mitsoko::ViewBase::onActivityResult(int requestCode,int resultCode, android::content::Intent data){
    //..
}
