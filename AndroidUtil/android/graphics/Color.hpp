
#pragma once

#include "Viper/AndroidUtil/java/lang/Class.hpp"

namespace android {
    namespace graphics {
        struct Color:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/graphics/Color");
            
#define STATIC_FINAL_INT(name) static int name(){ if(java::lang::Class cls=java::lang::Class::find<Color>()){ return cls.getStaticField<int>(#name); }else{ return -1; } }
            
            STATIC_FINAL_INT(BLACK)
            STATIC_FINAL_INT(DKGRAY)
            STATIC_FINAL_INT(GRAY)
            STATIC_FINAL_INT(LTGRAY)
            STATIC_FINAL_INT(WHITE)
            STATIC_FINAL_INT(RED)
            STATIC_FINAL_INT(GREEN)
            STATIC_FINAL_INT(BLUE)
            STATIC_FINAL_INT(YELLOW)
            STATIC_FINAL_INT(CYAN)
            STATIC_FINAL_INT(MAGENTA)
            STATIC_FINAL_INT(TRANSPARENT)
            
#undef STATIC_FINAL_INT
            
#endif
        };
    }
}
