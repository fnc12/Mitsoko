
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__EDIT_TEXT__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__EDIT_TEXT__

#include "TextView.hpp"
#include "Mitsoko/AndroidUtil/android/content/Context.hpp"
#include "Mitsoko/AndroidUtil/android/text/Editable.hpp"

namespace android{
    
    namespace widget{
        
        struct EditText : public TextView {
            
            using TextView::TextView;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/EditText");
            
            static EditText create(const content::Context &context);
            
            android::text::Editable getText();
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__EDIT_TEXT__
