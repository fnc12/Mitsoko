
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
#ifdef __APPLE__
    enum class KeyboardType{
        Default=UIKeyboardTypeDefault,
        ASCIICapable=UIKeyboardTypeASCIICapable,
        NumbersAndPunctuation=UIKeyboardTypeNumbersAndPunctuation,
        URL=UIKeyboardTypeURL,
        NumberPad=UIKeyboardTypeNumberPad,
        PhonePad=UIKeyboardTypePhonePad,
        NamePhonePad=UIKeyboardTypeNamePhonePad,
        EmailAddress=UIKeyboardTypeEmailAddress,
        DecimalPad=UIKeyboardTypeDecimalPad,
        Twitter=UIKeyboardTypeTwitter,
        WebSearch=UIKeyboardTypeWebSearch,
//        UIKeyboardTypeAlphabet = UIKeyboardTypeASCIICapable, // Deprecated
    };
#endif
    /**
     *  Protocol.
     */
    struct TextInputTraits: public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        void setKeyboardType(UI::KeyboardType newValue){
            this->sendMessage<void>("setKeyboardType:", UIKeyboardType(newValue));
        }
        
        UI::KeyboardType keyboardType(){
            return KeyboardType(this->sendMessage<UIKeyboardType>("keyboardType"));
        }
#endif
    };
}
