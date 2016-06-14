
#pragma once

#include "Viper/AndroidUtil/android/view/View.hpp"

namespace android{
    namespace widget{
        struct ImageView:public view::View{
            using View::View;
            STATIC_VAR(const std::string, signature, "android/widget/ImageView");
        };
    }
}
