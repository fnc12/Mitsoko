//
//  Image.cpp
//  GoZebra
//
//  Created by John Zakharov on 02.03.17.
//  Copyright © 2017 Outlaw Studio. All rights reserved.
//

#include "Image.hpp"

#ifdef __APPLE__

CG::Image::Image(decltype(handle) h):
handle(h){}

decltype(CGImageGetWidth(nullptr)) CG::Image::width() {
    return CGImageGetWidth(this->handle);
}

decltype(CGImageGetHeight(nullptr)) CG::Image::height() {
    return CGImageGetHeight(this->handle);
}

CG::Image CG::Image::createImageInRect(const Rect &rect) {
    return CGImageCreateWithImageInRect(this->handle, rect);
}

#endif  //  __APPLE__
