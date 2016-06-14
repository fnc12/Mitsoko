
#pragma once

namespace android{
    namespace widget{
        struct CheckBox:public CompoundButton{
            using CompoundButton::CompoundButton;
            STATIC_VAR(const std::string, signature, "android/widget/CheckBox");
        };
    }
}
