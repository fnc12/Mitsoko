//
//  Image.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Image.hpp"

#ifdef __APPLE__

const std::string UI::Image::className="UIImage";

UI::Image UI::Image::create(const std::string &named){
    auto cls=NS::getClass(className);
    auto str=CF::String::create(named);
    return NS::Object::sendMessage<Handle>(cls,"imageNamed:", str.handle);
}

UI::Image UI::Image::createWithContentsOfFile(const std::string &filename){
    auto s=CF::String::create(filename);
    return std::move(createWithContentsOfFile(s));
}

UI::Image UI::Image::createWithContentsOfFile(const CF::String &filename){
    auto cls=NS::getClass(className);
    return NS::Object::sendMessage<Handle>(cls,"imageWithContentsOfFile:", filename.handle);
}

NS::Data UI::Image::JPEGRepresentation(UI::Image image,CG::Float compressionQuality){
    image.retain();
    auto res=CFBridgingRetain(UIImageJPEGRepresentation(CFBridgingRelease(image.handle), CGFloat(compressionQuality)));
    CFRelease(res);
    return res;
}

CG::Size UI::Image::size(){
    return this->sendMessage<CGSize>("size");
}

#endif  //__APPLE__
