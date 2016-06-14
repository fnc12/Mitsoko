
#pragma once

#include "Viper/AndroidUtil/android/support/v4/app/FragmentActivity.hpp"

namespace android{
    namespace support{
        namespace v7{
            namespace app{
                struct AppCompatActivity:public android::support::v4::app::FragmentActivity{
                    using FragmentActivity::FragmentActivity;
                    STATIC_VAR(const std::string, signature, "android/support/v7/app/AppCompatActivity");
#ifdef __ANDROID__
                    void invalidateOptionsMenu(){
                        this->sendMessage<void>("invalidateOptionsMenu");
                    }
#endif
                };
            }
        }
    }
}
