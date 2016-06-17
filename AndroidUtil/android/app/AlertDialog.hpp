
#pragma once

#include "Dialog.hpp"

namespace android{
    namespace app{
        struct AlertDialog:public Dialog{
            using Dialog::Dialog;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/AlertDialog");
#endif
        };
    }
}
