
#pragma once

#include "Viper/AndroidUtil/android/content/Context.hpp"
#include "Viper/AndroidUtil/android/content/Intent.hpp"

namespace android{
    namespace app{
        struct Activity:public content::Context{
            using Context::Context;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/Activity");
            
            static int RESULT_CANCELED(){
                if(java::lang::Class cls=java::lang::Class::find<Activity>()){
                    return cls.getStaticField<int>("RESULT_CANCELED");
                }else{
                    return -1;
                }
            }
            
            static int RESULT_OK(){
                if(java::lang::Class cls=java::lang::Class::find<Activity>()){
                    return cls.getStaticField<int>("RESULT_OK");
                }else{
                    return -1;
                }
            }
            
            static int RESULT_FIRST_USER(){
                if(java::lang::Class cls=java::lang::Class::find<Activity>()){
                    return cls.getStaticField<int>("RESULT_FIRST_USER");
                }else{
                    return -1;
                }
            }
            
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
