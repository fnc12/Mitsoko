
#pragma once

#include "Viper/AndroidUtil/android/view/View.hpp"

namespace android{
    namespace widget{
        struct TextView:public view::View{
            using View::View;
            STATIC_VAR(const std::string, signature, "android/widget/TextView");
            
            void setText(const std::string &value){
#ifdef __ANDROID__
                if(auto java_env=java::lang::JNI::Env()){
                    if(auto setTextMethod=java_env->GetMethodID(this->getClass(),"setText","(Ljava/lang/CharSequence;)V")){
                        auto str=java::lang::String::create(value);
                        //                        auto str=java_env->NewStringUTF(value.c_str());
                        java_env->CallVoidMethod(static_cast<jobject>(const_cast<void*>(this->handle)),setTextMethod,(jobject)str.handle);
                    }else{
                        LOGI("setTextMethod is null");
                    }
                }
#endif
            }
        };
    }
}
