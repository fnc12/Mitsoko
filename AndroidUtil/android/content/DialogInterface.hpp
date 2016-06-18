
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace content{
        /**
         *  Interface.
         */
        struct DialogInterface:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/content/DialogInterface");
            
            void cancel(){
                this->sendMessage<void>("cancel");
            }
            
            void dismiss(){
                this->sendMessage<void>("dismiss");
            }
            
            struct OnClickListener:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/content/DialogInterface$OnClickListener");
                
            };
#endif
        };
    }
}