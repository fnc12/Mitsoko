
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace android{
    namespace text{
        struct Editable:public java::lang::_CharSequence<java::lang::String>{
            using _CharSequence::_CharSequence;
            STATIC_VAR(const std::string, signature, "android/text/Editable");
        };
    }
}
