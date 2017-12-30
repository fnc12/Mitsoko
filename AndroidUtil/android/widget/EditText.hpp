
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__EDIT_TEXT__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__EDIT_TEXT__

#include "TextView.hpp"
#include "Mitsoko/AndroidUtil/android/content/Context.hpp"
#include "Mitsoko/AndroidUtil/android/text/Editable.hpp"
#include "Mitsoko/AndroidUtil/java/lang/CharSequence.hpp"
#include "Mitsoko/AndroidUtil/android/text/TextWatcher.hpp"
#include "Mitsoko/Disposable.hpp"

#include <functional>

namespace android{
    
    namespace widget{
        
        struct EditText : public TextView {
            
            using TextView::TextView;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            static EditText create(const content::Context &context);
            
            android::text::Editable getText();
            
            void addTextChangedListener(std::function<void(java::lang::CharSequence, int, int, int)> beforeTextChanged,
                                        std::function<void(java::lang::CharSequence, int, int, int)> onTextChanged,
                                        std::function<void(android::text::Editable)> afterTextChanged,
                                        Mitsoko::Disposable &disposable);
            
            void addTextChangedListener(const android::text::TextWatcher &watcher);
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__EDIT_TEXT__
