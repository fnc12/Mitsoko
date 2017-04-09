//
//  File.cpp
//  Groozim
//
//  Created by John Zakharov on 15.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "File.hpp"

#ifdef __ANDROID__

const std::string java::io::File::signature = "java/io/File";

auto java::io::File::create(const std::string &path)->File{
    auto p=java::lang::String::create(path);
    return std::move(create(p));
}

auto java::io::File::create(const java::lang::String &path)->File{
    return std::move(java::lang::Object::create<File>(path));
}

#endif  //__ANDROID__
