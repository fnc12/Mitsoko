//
//  FilterOutputStream.cpp
//  Groozim
//
//  Created by John Zakharov on 15.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "FilterOutputStream.hpp"

#ifdef __ANDROID__

const std::string java::io::FilterOutputStream::signature = "java/io/FilterOutputStream";

#endif  //__ANDROID__
