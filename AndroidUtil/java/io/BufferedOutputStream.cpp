//
//  BufferedOutputStream.cpp
//  Groozim
//
//  Created by John Zakharov on 15.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "BufferedOutputStream.hpp"

#ifdef __ANDROID__

const std::string java::io::BufferedOutputStream::signature = "java/io/BufferedOutputStream";

auto java::io::BufferedOutputStream::create(const OutputStream &out)->BufferedOutputStream{
    return std::move(java::lang::Object::create<BufferedOutputStream>(out));
}

#endif  //__ANDROID__
