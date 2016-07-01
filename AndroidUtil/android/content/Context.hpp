
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/android/content/res/Resources.hpp"

namespace android{
    namespace content{
        struct Context:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/content/Context");
            
            res::Resources getResources(){
                return this->sendMessage<res::Resources>("getResources");
            }
            
            java::lang::String getPackageName(){
                return this->sendMessage<java::lang::String>("getPackageName");
            }
#endif
        };
    }
}
