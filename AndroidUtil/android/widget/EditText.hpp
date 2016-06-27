
#pragma once

#include "TextView.hpp"
#include "Viper/AndroidUtil/android/content/Context.hpp"

namespace android{
    namespace widget{
        struct EditText:public TextView{
            using TextView::TextView;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/EditText");
            
            static EditText create(const content::Context &context){
                return std::move(java::lang::Object::create<EditText>(context));
            }
            
            android::text::Editable getText(){
                return this->sendMessage<android::text::Editable>("getText");
            }
#endif
        };
    }
}
