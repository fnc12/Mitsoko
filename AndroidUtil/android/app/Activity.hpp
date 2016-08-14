
#ifndef __VIPER__ANDROID_UTIL__ANDROID__APP_ACTIVITY__
#define __VIPER__ANDROID_UTIL__ANDROID__APP_ACTIVITY__

#include "Viper/AndroidUtil/android/content/Context.hpp"
#include "Viper/AndroidUtil/android/content/Intent.hpp"

namespace android{
    namespace app{
        struct Activity:public content::Context{
            using Context::Context;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/Activity");
            
            static int RESULT_CANCELED();
            
            static int RESULT_OK();
            
            static int RESULT_FIRST_USER();
            
            void finish();
            
            void startActivity(const content::Intent &intent);
            
            void startActivityForResult(const content::Intent &intent, int requestCode);
            
            void setResult(int resultCode);
            
            void setResult(int resultCode,const content::Intent &intent);
            
            void runOnUiThread(const java::lang::Runnable &runnable);
#endif
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__APP_ACTIVITY__
