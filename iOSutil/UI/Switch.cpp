//
//  Switch.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Switch.hpp"

#ifdef __APPLE__

const std::string UI::Switch::className="UISwitch";

void UI::Switch::setOn(bool newValue){
    this->sendMessage<void>("setOn:",newValue);
}

bool UI::Switch::on(){
    return this->sendMessage<bool>("isOn");
}

#endif  //__APPLE__
