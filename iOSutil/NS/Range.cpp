//
//  Range.cpp
//  Groozim
//
//  Created by John Zakharov on 05.09.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Range.hpp"

#ifdef __APPLE__

NS::Range::Range(const NSRange &s):NSRange(s){}

#endif  //__APPLE__
