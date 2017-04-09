//
//  OutputStream.cpp
//  Groozim
//
//  Created by John Zakharov on 15.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "OutputStream.hpp"

#ifdef __ANDROID__

const std::string java::io::OutputStream::signature = "java/io/OutputStream";

void java::io::OutputStream::close(){
    this->sendMessage<void>("close");
}

#endif  //__ANDROID__
