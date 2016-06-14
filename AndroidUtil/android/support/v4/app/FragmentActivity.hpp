
#pragma once

#include "Viper/AndroidUtil/android/app/Activity.hpp"

namespace android{
    namespace support{
        namespace v4{
            namespace app{
                struct FragmentActivity:public android::app::Activity{
                    using Activity::Activity;
                    STATIC_VAR(const std::string, signature, "android/support/v4/app/FragmentActivity");
                };
            }
        }
    }
}
