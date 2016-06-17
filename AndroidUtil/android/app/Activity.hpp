
#pragma once

#include "Viper/AndroidUtil/android/content/Context.hpp"
#include "Viper/AndroidUtil/android/content/Intent.hpp"

namespace android{
    namespace app{
        struct Activity:public content::Context{
            using Context::Context;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/Activity");
            
            void finish(){
                this->sendMessage<void>("finish");
            }
            
            void startActivity(const content::Intent &intent){
                this->sendMessage<void>("startActivity",intent);
            }
            
            void startActivityForResult(const content::Intent &intent, int requestCode){
                this->sendMessage<void>("startActivityForResult",intent,requestCode);
            }
            
            void setResult(int resultCode){
                this->sendMessage<void>("setResult",resultCode);
            }
            
            void setResult(int resultCode,const content::Intent &intent){
                this->sendMessage<void>("setResult",resultCode,intent);
            }
            
            void runOnUiThread(const java::lang::Runnable &runnable){
                this->sendMessage<void>("runOnUiThread",runnable);
            }
#endif
        };
    }
}
