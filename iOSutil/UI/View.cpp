//
//  View.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "View.hpp"

#ifdef __APPLE__

void UI::View::addSubview(const UI::View &view){
    this->sendMessage<void>("addSubview:", view.handle);
}

void UI::View::setBackgroundColor(const UI::Color &newValue){
    this->sendMessage<void>("setBackgroundColor:", newValue.handle);
}

UI::Color UI::View::backgroundColor(){
    return this->sendMessage<Handle>("backgroundColor");
}

void UI::View::setFrame(const CG::Rect &newValue){
    this->sendMessage<void>("setFrame:", CGRect(newValue));
}

void UI::View::setContentMode(ContentMode newValue){
    this->sendMessage<void>("setContentMode:", UIViewContentMode(newValue));
}

auto UI::View::contentMode()->ContentMode{
    return ContentMode(this->sendMessage<UIViewContentMode>("contentMode"));
}

void UI::View::setHidden(bool newValue){
    this->sendMessage<void>("setHidden:", newValue);
}

void UI::View::setTransform(const CG::AffineTransform &newValue){
    this->sendMessage<void>("setTransform:", newValue);
}

CG::AffineTransform UI::View::transform(){
    return this->sendMessage<CGAffineTransform>("transform");
}

#endif  //__APPLE__
