//
//  String.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "String.hpp"

#ifdef __APPLE__

const std::string NS::String::className="NSString";

const char* NS::String::UTF8String(){
    return this->sendMessage<const char*>("UTF8String");
}

#endif  //__APPLE__
