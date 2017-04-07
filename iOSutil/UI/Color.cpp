//
//  Color.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Color.hpp"

#ifdef __APPLE__

const std::string UI::Color::className = "UIColor";

UI::Color UI::Color::colorWithRedGreenBlueAlpha(CG::Float red, CG::Float green, CG::Float blue, CG::Float alpha) {
    auto cls = NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls, "colorWithRed:green:blue:alpha:", red, green, blue, alpha);
}

#endif  //__APPLE__
