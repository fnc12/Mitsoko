
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace view{
        struct Window:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/view/Window");
            
            void setSoftInputMode(int mode){
                this->sendMessage<void>("setSoftInputMode",mode);
            }
#endif
        };
    }
}
