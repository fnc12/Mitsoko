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
    return this->sendMessage<bool>("resignFirstResponder");
}

#endif  //__APPLE__
