
#pragma once

#include "TextView.hpp"

namespace android{
    namespace widget{
        struct EditText:public TextView{
            using TextView::TextView;
            STATIC_VAR(const std::string, signature, "android/widget/EditText");
#ifdef __ANDROID__
            android::text::Editable getText(){
                return this->sendMessage<android::text::Editable>("getText");
            }
#endif
        };
    }
}
