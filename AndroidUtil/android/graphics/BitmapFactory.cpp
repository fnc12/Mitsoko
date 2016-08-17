//
//  BitmapFactory.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "BitmapFactory.hpp"

#ifdef __ANDROID__

//const std::string android::graphics::BitmapFactory::signature="android/graphics/BitmapFactory";

//const std::string android::graphics::BitmapFactory::Options::signature="android/graphics/BitmapFactory$Options";

auto android::graphics::BitmapFactory::decodeFile(const std::string &pathName)->Bitmap{
    auto s=java::lang::String::create(pathName);
    return std::move(decodeFile(s));
}

auto android::graphics::BitmapFactory::decodeFile(const java::lang::String &pathName)->Bitmap{
    if(auto java_env=java::lang::JNI::Env()){
        auto clazz = java_env->FindClass(signature().c_str());
        auto methodSignature=generateMethodSignature<Bitmap,java::lang::String>();
        auto mid=java_env->GetStaticMethodID(clazz,"decodeFile",methodSignature.c_str());
        return java_env->CallStaticObjectMethod(clazz,mid,(jobject)pathName.handle);
    }else{
        return {};
    }
}

auto android::graphics::BitmapFactory::Options::create()->Options{
    return std::move(java::lang::Object::create<Options>());
}

#endif  //__ANDROID__
