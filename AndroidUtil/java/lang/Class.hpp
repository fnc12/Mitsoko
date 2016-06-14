
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        struct Class:public Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/lang/Class");
#ifdef __ANDROID__
            static jclass find(const std::string &signature){
                if(auto env=JNI::Env()){
                    return env->FindClass(signature.c_str());
                }else{
                    LOGI("env is null");
                    return nullptr;
                }
            }
            
            template<class T>
            static jclass find(){
                return find(T::signature());
            }
#endif
        };
    }
}
