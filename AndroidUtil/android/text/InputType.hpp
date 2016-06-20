
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
            
            static int TYPE_NUMBER_FLAG_SIGNED(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_NUMBER_FLAG_SIGNED");
                }else{
                    return -1;
                }
            }
            
            static int TYPE_NUMBER_FLAG_DECIMAL(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_NUMBER_FLAG_DECIMAL");
                }else{
                    return -1;
                }
            }
            
            static int TYPE_CLASS_NUMBER(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_CLASS_NUMBER");
                }else{
                    return -1;
                }
            }
            
            static int TYPE_CLASS_TEXT(){
                if(java::lang::Class cls=java::lang::Class::find<InputType>()){
                    return cls.getStaticField<int>("TYPE_CLASS_TEXT");
                }else{
                    return -1;
                }
            }
#endif
        };
    }
}
