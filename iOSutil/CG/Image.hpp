//
//  Image.hpp
//  GoZebra
//
//  Created by John Zakharov on 02.03.17.
//  Copyright © 2017 Outlaw Studio. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#ifdef __APPLE__

#include "CG.hpp"
#include "Rect.hpp"

namespace CG {
    
    struct Image {
        
        typedef CGImageRef Ref;
        
        Ref handle;
        
        Image(decltype(handle));
        
        decltype(CGImageGetWidth(nullptr)) width();
        
        decltype(CGImageGetHeight(nullptr)) height();
        
        Image createImageInRect(const Rect &rect);
    };
}

#endif

#endif /* Image_hpp */
