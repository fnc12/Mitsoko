
#pragma once

#include "Viper/AndroidUtil/android/view/View.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace android{
    namespace widget{
        struct TextView:public view::View{
            using View::View;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/TextView");
            
            void setInputType(int type){
                this->sendMessage<void>("setInputType",type);
            }
            
            /*std::string getText(){
                auto res=this->sendMessage<java::lang::CharSequence>("getText").toString();
                return res.c_str();
            }*/
            
            void setText(const std::string &value){
//                if(auto java_env=java::lang::JNI::Env()){
//                    if(auto setTextMethod=java_env->GetMethodID(this->getClass(),"setText","(Ljava/lang/CharSequence;)V")){
                        auto str=java::lang::String::create(value);
                        this->setText(str);
                    /*}else{
                        LOGI("setTextMethod is null");
                    }*/
//                }
            }
            
            void setText(const java::lang::String &str){
                this->sendMessage<void>("setText",(java::lang::CharSequence)str);
//                java_env->CallVoidMethod(static_cast<jobject>(const_cast<void*>(this->handle)),setTextMethod,(jobject)str.handle);
            }
#endif
        };
    }
}
