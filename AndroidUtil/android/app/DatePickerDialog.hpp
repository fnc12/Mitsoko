
#ifndef __VIPER__ANDROID_UTIL__ANDROID__APP__DATE_PICKER_DIALOG__
#define __VIPER__ANDROID_UTIL__ANDROID__APP__DATE_PICKER_DIALOG__

#include "AlertDialog.hpp"

namespace android{
    
    namespace app{
        
        struct DatePickerDialog : public AlertDialog {
            
            using AlertDialog::AlertDialog;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "android/app/DatePickerDialog");
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__APP__DATE_PICKER_DIALOG__
