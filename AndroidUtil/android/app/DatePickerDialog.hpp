
#pragma once

#include "AlertDialog.hpp"

namespace android{
    namespace app{
        struct DatePickerDialog:public AlertDialog{
            using AlertDialog::AlertDialog;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/DatePickerDialog");
#endif
        };
    }
}
