//
//  Bitmap.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Bitmap.hpp"
#include "Viper/AndroidUtil/java/lang/Class.hpp"

using std::cout;
using std::endl;

#ifdef __ANDROID__

//const std::string android::graphics::Bitmap::signature="android/graphics/Bitmap";

//const std::string android::graphics::Bitmap::CompressFormat::signature="android/graphics/Bitmap$CompressFormat";

//const std::string android::graphics::Bitmap::Config::signature="android/graphics/Bitmap$Config";

void android::graphics::Bitmap::recycle(){
    this->sendMessage<void>("recycle");
}

int android::graphics::Bitmap::getWidth(){
    return this->sendMessage<int>("getWidth");
}

int android::graphics::Bitmap::getHeight(){
    return this->sendMessage<int>("getHeight");
}

int android::graphics::Bitmap::CompressFormat::JPEG(){
    if(java::lang::Class cls=java::lang::Class::find<CompressFormat>()){
        return cls.getStaticField<int>("JPEG");
    }else{
        return -1;
    }
}

int android::graphics::Bitmap::CompressFormat::PNG(){
    if(java::lang::Class cls=java::lang::Class::find<CompressFormat>()){
        return cls.getStaticField<int>("PNG");
    }else{
        return -1;
    }
}

int android::graphics::Bitmap::CompressFormat::WEBP(){
    if(java::lang::Class cls=java::lang::Class::find<CompressFormat>()){
        return cls.getStaticField<int>("WEBP");
    }else{
        return -1;
    }
}

int android::graphics::Bitmap::Config::ALPHA_8(){
    if(java::lang::Class cls=java::lang::Class::find<Config>()){
        return cls.getStaticField<int>("ALPHA_8");
    }else{
        return -1;
    }
}

int android::graphics::Bitmap::Config::RGB_565(){
    if(java::lang::Class cls=java::lang::Class::find<Config>()){
        return cls.getStaticField<int>("RGB_565");
    }else{
        return -1;
    }
}

int android::graphics::Bitmap::Config::ARGB_4444(){
    if(java::lang::Class cls=java::lang::Class::find<Config>()){
        return cls.getStaticField<int>("ARGB_4444");
    }else{
        return -1;
    }
}

int android::graphics::Bitmap::Config::ARGB_8888(){
    if(java::lang::Class cls=java::lang::Class::find<Config>()){
        return cls.getStaticField<int>("ARGB_8888");
    }else{
        return -1;
    }
}

bool android::graphics::Bitmap::compress(int format,int quality,const java::io::OutputStream &stream){
    return this->sendMessage<bool>("compress",format,quality,stream);
}

auto android::graphics::Bitmap::createScaledBitmap(const Bitmap &src, int dstWidth, int dstHeight, bool filter)->Bitmap{
    if(auto java_env=java::lang::JNI::Env()){
        auto clazz = java_env->FindClass(signature().c_str());
//        cout<<"clazz = "<<clazz<<endl;
        auto methodSignature=generateMethodSignature<Bitmap,Bitmap,int,int,bool>();
//        cout<<"methodSignature = "<<methodSignature<<endl;
        auto mid=java_env->GetStaticMethodID(clazz,"createScaledBitmap",methodSignature.c_str());
//        cout<<"mid = "<<mid<<endl;
        return java_env->CallStaticObjectMethod(clazz, mid, src.handle, jint(dstWidth), jint(dstHeight), jboolean(filter));
    }else{
        return {};
    }
}

#endif  //__ANDROID__
