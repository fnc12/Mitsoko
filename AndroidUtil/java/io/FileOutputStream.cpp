//
//  FileOutputStream.cpp
//  Groozim
//
//  Created by John Zakharov on 15.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "FileOutputStream.hpp"

#ifdef __ANDROID__

//const std::string java::io::File::signature="java/io/FileOutputStream";

auto java::io::FileOutputStream::create(const File &file)->FileOutputStream{
    return java::lang::Object::create<FileOutputStream>(file);
}

#endif  //__ANDROID__
