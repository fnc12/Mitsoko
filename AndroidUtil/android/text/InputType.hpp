
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

            STATIC_JINT(TYPE_CLASS_PHONE);
            STATIC_JINT(TYPE_NUMBER_FLAG_SIGNED);
            STATIC_JINT(TYPE_NUMBER_FLAG_DECIMAL);
            STATIC_JINT(TYPE_CLASS_NUMBER);
            STATIC_JINT(TYPE_CLASS_TEXT);
            STATIC_JINT(TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
            
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
