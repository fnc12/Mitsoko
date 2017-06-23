//
//  ByteArrayOutputStream.cpp
//  MyBusiness
//
//  Created by John Zakharov on 23.06.17.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#include "ByteArrayOutputStream.hpp"

#ifdef __ANDROID__

const std::string java::io::ByteArrayOutputStream::signature = "java/io/ByteArrayOutputStream";

java::io::ByteArrayOutputStream java::io::ByteArrayOutputStream::create() {
    return java::lang::Object::create<ByteArrayOutputStream>();
}

java::lang::Array<char> java::io::ByteArrayOutputStream::toByteArray() {
    return this->sendMessage<java::lang::Array<char>>("toByteArray");
}

#endif  //  __ANDROID__
