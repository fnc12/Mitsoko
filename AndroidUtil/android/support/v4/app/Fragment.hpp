
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace support{
        namespace v4{
            namespace app{
                struct Fragment:public java::lang::Object{
                    using Object::Object;
                    STATIC_VAR(const std::string, signature, "android/support/v4/app/Fragment");
#ifdef __ANDROID__
                    FragmentActivity getActivity(){
                        return this->sendMessage<FragmentActivity>("getActivity");
                    }
#endif
                };
            }
        }
    }
}
