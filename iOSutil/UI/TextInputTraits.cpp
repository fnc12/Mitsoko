//
//  TextInputTraits.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TextInputTraits.hpp"

#ifdef __APPLE__

void UI::TextInputTraits::setKeyboardType(UI::KeyboardType newValue){
    this->sendMessage<void>("setKeyboardType:", UIKeyboardType(newValue));
}

UI::KeyboardType UI::TextInputTraits::keyboardType(){
    return KeyboardType(this->sendMessage<UIKeyboardType>("keyboardType"));
}

#endif  //__APPLE__
