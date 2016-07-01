
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Viper/AndroidUtil/android/net/Uri.hpp"
#include "Viper/AndroidUtil/android/os/Bundle.hpp"
#include "Viper/AndroidUtil/android/net/Uri.hpp"

namespace android{
    namespace content{
        struct Intent:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/content/Intent");
            
            static Intent create(const Context &context,const java::lang::Class &cls){
                return std::move(java::lang::Object::create<Intent>(context,cls));
            }
            
            static Intent create(const java::lang::String &action,const android::net::Uri &uri){
                return std::move(java::lang::Object::create<Intent>(action,uri));
            }
            
            static Intent create(const java::lang::String &action){
                return std::move(java::lang::Object::create<Intent>(action));
            }
            
            static java::lang::String ACTION_PICK(){
                if(java::lang::Class cls=java::lang::Class::find<Intent>()){
                    return cls.getStaticField<java::lang::String>("ACTION_PICK");
                }else{
                    return {};
                }
            }
            
            android::net::Uri getData(){
                return this->sendMessage<android::net::Uri>("getData");
            }
            
            android::os::Bundle getExtras(){
                return this->sendMessage<android::os::Bundle>("getExtras");
            }
            
            Intent& putExtra(const std::string &name,const std::string &value){
                auto j_name=java::lang::String::create(name);
                auto j_value=java::lang::String::create(value);
                this->sendMessage<Intent>("putExtra",j_name,j_value);
                return *this;
            }
#endif
        };
    }
}
