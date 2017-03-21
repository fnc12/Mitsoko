//
//  Responder.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Responder.hpp"

#ifdef __APPLE__

const std::string UI::Responder::className="UIResponder";

bool UI::Responder::resignFirstResponder(){
    return this->sendMessage<BOOL>("resignFirstResponder");
}

bool UI::Responder::becomeFirstResponder() {
    return this->sendMessage<BOOL>("becomeFirstResponder");
}

bool UI::Responder::canBecomeFirstResponder() {
    return this->sendMessage<BOOL>("canBecomeFirstResponder");
}

UI::Responder UI::Responder::nextResponder() {
    return this->sendMessage<Handle>("nextResponder");
}

bool UI::Responder::canResignFirstResponder() {
    return this->sendMessage<BOOL>("canResignFirstResponder");
}

bool UI::Responder::isFirstResponder() {
    return this->sendMessage<BOOL>("isFirstResponder");
}

#endif  //__APPLE__
