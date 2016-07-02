
#pragma once

#include "Viper/AndroidUtil/java/lang/Object.hpp"
#include "Viper/AndroidUtil/java/io/OutputStream.hpp"

namespace android {
    namespace graphics {
        struct Bitmap:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/graphics/Bitmap");
            
            int getWidth(){
                return this->sendMessage<int>("getWidth");
            }
            
            int getHeight(){
                return this->sendMessage<int>("getHeight");
            }
            
            struct CompressFormat:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/graphics/Bitmap$CompressFormat");
                
                static int JPEG(){
                    if(java::lang::Class cls=java::lang::Class::find<CompressFormat>()){
                        return cls.getStaticField<int>("JPEG");
                    }else{
                        return -1;
                    }
                }
                
                static int PNG(){
                    if(java::lang::Class cls=java::lang::Class::find<CompressFormat>()){
                        return cls.getStaticField<int>("PNG");
                    }else{
                        return -1;
                    }
                }
                
                static int WEBP(){
                    if(java::lang::Class cls=java::lang::Class::find<CompressFormat>()){
                        return cls.getStaticField<int>("WEBP");
                    }else{
                        return -1;
                    }
                }
            };
            
            struct Config:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/graphics/Bitmap$Config");
                
                static int ALPHA_8(){
                    if(java::lang::Class cls=java::lang::Class::find<Config>()){
                        return cls.getStaticField<int>("ALPHA_8");
                    }else{
                        return -1;
                    }
                }
                
                static int RGB_565(){
                    if(java::lang::Class cls=java::lang::Class::find<Config>()){
                        return cls.getStaticField<int>("RGB_565");
                    }else{
                        return -1;
                    }
                }
                
                static int ARGB_4444(){
                    if(java::lang::Class cls=java::lang::Class::find<Config>()){
                        return cls.getStaticField<int>("ARGB_4444");
                    }else{
                        return -1;
                    }
                }
                
                static int ARGB_8888(){
                    if(java::lang::Class cls=java::lang::Class::find<Config>()){
                        return cls.getStaticField<int>("ARGB_8888");
                    }else{
                        return -1;
                    }
                }
            };
            
            bool compress(int format,int quality,const java::io::OutputStream &stream){
                return this->sendMessage<bool>("compress",format,quality,stream);
            }
            
            static Bitmap createScaledBitmap(const Bitmap &src, int dstWidth, int dstHeight, bool filter){
                if(auto java_env=java::lang::JNI::Env()){
                    auto clazz = java_env->FindClass(signature().c_str());
                    auto methodSignature=generateMethodSignature<Bitmap,Bitmap,int,int,bool>();
                    auto mid=java_env->GetStaticMethodID(clazz,"createScaledBitmap",methodSignature.c_str());
                    return java_env->CallStaticObjectMethod(clazz,mid);
                }else{
                    return {};
                }
            }
#endif
        };
    }
}
