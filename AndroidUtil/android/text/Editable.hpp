
#pragma once

#include "Viper/AndroidUtil/java/lang/CharSequence.hpp"

namespace android{
    namespace text{
        struct Editable:public java::lang::CharSequence{
            using CharSequence::CharSequence;
            STATIC_VAR(const std::string, signature, "android/text/Editable");
        };
    }
}
