
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"

namespace android{
    namespace text{
        
        /**
         *  Interface.
         */
        struct InputType:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/text/InputType");
            
#define STATIC_JINT(name) static int name(){\
            if(java::lang::Class cls=java::lang::Class::find<InputType>()){\
                return cls.getStaticField<int>(#name);\
            }else{\
                return -1;\
            }\
        }\

            STATIC_JINT(TYPE_MASK_CLASS);
            STATIC_JINT(TYPE_MASK_VARIATION);
            STATIC_JINT(TYPE_MASK_FLAGS);
            STATIC_JINT(TYPE_NULL);
            STATIC_JINT(TYPE_CLASS_TEXT);
            STATIC_JINT(TYPE_TEXT_FLAG_CAP_CHARACTERS);
            STATIC_JINT(TYPE_TEXT_FLAG_CAP_WORDS);
            STATIC_JINT(TYPE_TEXT_FLAG_CAP_SENTENCES);
            STATIC_JINT(TYPE_TEXT_FLAG_AUTO_CORRECT);
            STATIC_JINT(TYPE_TEXT_FLAG_AUTO_COMPLETE);
            STATIC_JINT(TYPE_TEXT_FLAG_MULTI_LINE);
            STATIC_JINT(TYPE_TEXT_FLAG_IME_MULTI_LINE);
            STATIC_JINT(TYPE_TEXT_FLAG_NO_SUGGESTIONS);
            STATIC_JINT(TYPE_TEXT_VARIATION_NORMAL);
            STATIC_JINT(TYPE_TEXT_VARIATION_URI);
            STATIC_JINT(TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
            STATIC_JINT(TYPE_TEXT_VARIATION_EMAIL_SUBJECT);
            STATIC_JINT(TYPE_TEXT_VARIATION_SHORT_MESSAGE);
            STATIC_JINT(TYPE_TEXT_VARIATION_LONG_MESSAGE);
            STATIC_JINT(TYPE_TEXT_VARIATION_PERSON_NAME);
            STATIC_JINT(TYPE_TEXT_VARIATION_POSTAL_ADDRESS);
            STATIC_JINT(TYPE_TEXT_VARIATION_PASSWORD);
            STATIC_JINT(TYPE_TEXT_VARIATION_VISIBLE_PASSWORD);
            STATIC_JINT(TYPE_TEXT_VARIATION_WEB_EDIT_TEXT);
            STATIC_JINT(TYPE_TEXT_VARIATION_FILTER);
            STATIC_JINT(TYPE_TEXT_VARIATION_PHONETIC);
            STATIC_JINT(TYPE_TEXT_VARIATION_WEB_EMAIL_ADDRESS);
            STATIC_JINT(TYPE_TEXT_VARIATION_WEB_PASSWORD);
            STATIC_JINT(TYPE_CLASS_NUMBER);
            STATIC_JINT(TYPE_NUMBER_FLAG_SIGNED);
            STATIC_JINT(TYPE_NUMBER_FLAG_DECIMAL);
            STATIC_JINT(TYPE_NUMBER_VARIATION_NORMAL);
            STATIC_JINT(TYPE_NUMBER_VARIATION_PASSWORD);
            STATIC_JINT(TYPE_CLASS_PHONE);
            STATIC_JINT(TYPE_CLASS_DATETIME);
            STATIC_JINT(TYPE_DATETIME_VARIATION_NORMAL);
            STATIC_JINT(TYPE_DATETIME_VARIATION_DATE);
            STATIC_JINT(TYPE_DATETIME_VARIATION_TIME);
            
            
            /*static int TYPE_CLASS_PHONE(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_CLASS_PHONE");
                }else{
                    return -1;
                }
            }*/
            
            /*static int TYPE_NUMBER_FLAG_SIGNED(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_NUMBER_FLAG_SIGNED");
                }else{
                    return -1;
                }
            }*/
            
            /*static int TYPE_NUMBER_FLAG_DECIMAL(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_NUMBER_FLAG_DECIMAL");
                }else{
                    return -1;
                }
            }*/
            
            /*static int TYPE_CLASS_NUMBER(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_CLASS_NUMBER");
                }else{
                    return -1;
                }
            }*/
            
            /*static int TYPE_CLASS_TEXT(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_CLASS_TEXT");
                }else{
                    return -1;
                }
            }*/
            
#undef STATIC_JINT
#endif
        };
    }
}
