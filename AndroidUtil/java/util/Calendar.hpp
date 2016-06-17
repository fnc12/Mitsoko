
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Date.hpp"

namespace java{
    namespace util{
        struct Calendar:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/util/Calendar");
            
            void setTime(const Date &date){
                this->sendMessage<void>("setTime",date);
            }
            
            static Calendar getInstance(){
                if(auto java_env=java::lang::JNI::Env()){
                    auto clazz = java_env->FindClass(signature().c_str());
                    auto mid=java_env->GetStaticMethodID(clazz,"getInstance",generateMethodSignature<Calendar>().c_str());
                    return java_env->CallStaticObjectMethod(clazz,mid);
                }else{
                    return {};
                }
            }
#endif
        };
    }
}
