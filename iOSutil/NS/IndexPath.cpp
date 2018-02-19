//
//  IndexPath.cpp
//  mitsoko_ios
//
//  Created by John Zakharov on 19.02.2018.
//  Copyright © 2018 Mitsoko. All rights reserved.
//

#include "IndexPath.hpp"

#ifdef __APPLE__

const std::string NS::IndexPath::className = "NSIndexPath";

NS::IndexPath NS::IndexPath::createForRowInSection(int row, int section) {
    auto cls = NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls, "indexPathForRow:inSection:", NSInteger(row), NSInteger(section));
}

#endif  //  __APPLE__
