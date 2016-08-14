//
//  Array.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Array.hpp"

#ifdef __APPLE__

const std::string NS::Array::className="NSArray";

int NS::Array::count(){
    return int(this->sendMessage<NSUInteger>("count"));
}

auto NS::Array::operator[](int i)->Handle{
    return this->sendMessage<Handle>("objectAtIndex:", NSUInteger(i));
}

#endif  //__APPLE__
