
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Bitmap.hpp"

namespace android {
    namespace graphics {
        struct BitmapFactory:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/graphics/BitmapFactory");
            
            static Bitmap decodeFile(const std::string &pathName){
                auto s=java::lang::String::create(pathName);
//                java::lang::JNI::Env()->ExceptionCheck();
                return std::move(decodeFile(s));
            }
            
            static Bitmap decodeFile(const java::lang::String &pathName){
                if(auto java_env=java::lang::JNI::Env()){
                    auto clazz = java_env->FindClass(signature().c_str());
                    auto methodSignature=generateMethodSignature<Bitmap,java::lang::String>();
                    auto mid=java_env->GetStaticMethodID(clazz,"decodeFile",methodSignature.c_str());
                    return java_env->CallStaticObjectMethod(clazz,mid,(jobject)pathName.handle);
                }else{
                    return {};
                }
            }
            
            struct Options:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/graphics/BitmapFactory$Options");
                
                static Options create(){
                    return std::move(java::lang::Object::create<Options>());
                }
                
                /**
                 *  Enum setter
                 */
                /*void inPreferredConfig(int value){
                    this->setField<Bitmap::Config>("inPreferredConfig",value);
                }*/
                
            };
#endif
        };
    }
}
