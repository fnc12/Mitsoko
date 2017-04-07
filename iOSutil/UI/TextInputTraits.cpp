//
//  TextInputTraits.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TextInputTraits.hpp"

#ifdef __APPLE__

const std::string UI::TextInputTraits::className="UITextInputTraits";

void UI::TextInputTraits::setKeyboardType(UI::KeyboardType newValue){
    this->sendMessage<void>("setKeyboardType:", UIKeyboardType(newValue));
}

UI::KeyboardType UI::TextInputTraits::keyboardType(){
    return KeyboardType(this->sendMessage<UIKeyboardType>("keyboardType"));
}

void UI::TextInputTraits::setSecureTextEntry(bool value) {
    this->sendMessage<void>("setSecureTextEntry:", BOOL(value));
}

bool UI::TextInputTraits::isSecureTextEntry() {
    return this->sendMessage<BOOL>("isSecureTextEntry");
}

#endif  //__APPLE__
