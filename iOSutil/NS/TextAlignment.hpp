//
//  TextAlignment.hpp
//  MyBusiness
//
//  Created by John Zakharov on 20.05.17.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#ifndef TextAlignment_hpp
#define TextAlignment_hpp

#ifdef __APPLE__
#include <UIKit/NSText.h>
#endif

namespace NS {
    
    enum class TextAlignment {
#ifdef __APPLE__
        Left = NSTextAlignmentLeft,

        Center = NSTextAlignmentCenter,
        Right = NSTextAlignmentRight,
        Justified = NSTextAlignmentJustified,
        Natural = NSTextAlignmentNatural,
#endif
    };
}

#endif /* TextAlignment_hpp */
