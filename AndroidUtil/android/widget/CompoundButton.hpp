
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__COMPOUND_BUTTON__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__COMPOUND_BUTTON__

#include "Button.hpp"
#include <functional>
#include <map>

namespace android{
    
    namespace widget{
        
        struct CompoundButton:public Button{
            
            using Button::Button;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/CompoundButton");
            
            typedef std::function<void(CompoundButton,bool)> OnCheckedChangeCallback;
            typedef std::map<int,OnCheckedChangeCallback> OnCheckedMap;
            static OnCheckedMap onCheckedMap;
//            STATIC_VAR(OnCheckedMap, onCheckedMap, {});
            
            struct OnCheckedChangeListener:public java::lang::Object{
                
                using Object::Object;
                
//            const std::string signature;
                STATIC_VAR(const std::string, signature, "android/widget/CompoundButton$OnCheckedChangeListener");
            };
            
            static void onCheckedChanged(int id,jobject sender,bool checked);
            
            void setChecked(bool newValue);
            
            bool isChecked();
            
            /**
             *  TODO: add removal of callback on disposable dispose..
             */
            void setOnCheckedChangeListener(OnCheckedChangeCallback cb);
            
#endif
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__COMPOUND_BUTTON__
