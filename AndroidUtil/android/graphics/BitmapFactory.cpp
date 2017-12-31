//
//  BitmapFactory.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "BitmapFactory.hpp"
#include "Mitsoko/AndroidUtil/java/lang/Class.hpp"

#ifdef __ANDROID__

const std::string android::graphics::BitmapFactory::signature = "android/graphics/BitmapFactory";

const std::string android::graphics::BitmapFactory::Options::signature = "android/graphics/BitmapFactory$Options";

android::graphics::Bitmap android::graphics::BitmapFactory::decodeFile(const std::string &pathName) {
    auto s = java::lang::String::create(pathName);
    return decodeFile(s);
}

android::graphics::Bitmap android::graphics::BitmapFactory::decodeFile(const java::lang::String &pathName) {
    /*if(auto java_env = java::lang::JNI::Env()){
        auto clazz = java::lang::Class::find<BitmapFactory>();
        auto methodSignature = generateMethodSignature<Bitmap,java::lang::String>();
        auto mid = java_env->GetStaticMethodID(clazz, "decodeFile", methodSignature.c_str());
        return java_env->CallStaticObjectMethod(clazz,mid,(jobject)pathName.handle);
    }else{
        return {};
    }*/
    if(java::lang::Class cls = java::lang::Class::find<BitmapFactory>()){
        return cls.callStaticFunc<Bitmap>("decodeFile", pathName);
    }else{
        return {};
    }
}

android::graphics::Bitmap android::graphics::BitmapFactory::decodeFile(const java::lang::String &pathName, Options opts) {
    if(java::lang::Class cls = java::lang::Class::find<BitmapFactory>()){
        return cls.callStaticFunc<Bitmap>("decodeFile", pathName, opts);
    }else{
        return {};
    }
}

android::graphics::Bitmap android::graphics::BitmapFactory::decodeByteArray(java::lang::Array<char> data, int offset, int length) {
    if(java::lang::Class cls = java::lang::Class::find<BitmapFactory>()){
        return cls.callStaticFunc<Bitmap>("decodeByteArray", data, offset, length);
    }else{
        return {};
    }
}

auto android::graphics::BitmapFactory::Options::create() -> Options {
    return std::move(java::lang::Object::create<Options>());
}

android::graphics::Bitmap android::graphics::BitmapFactory::Options::inBitmap() {
    return this->getField<Bitmap>("inBitmap");
}

void android::graphics::BitmapFactory::Options::inBitmap(Bitmap value) {
    this->setField("inBitmap", value);
}

int android::graphics::BitmapFactory::Options::inDensity() {
    return this->getField<int>("inDensity");
}

void android::graphics::BitmapFactory::Options::inDensity(int value) {
    this->setField("inDensity", value);
}

bool android::graphics::BitmapFactory::Options::inDither() {
    return this->getField<bool>("inDither");
}

void android::graphics::BitmapFactory::Options::inDither(bool value) {
    this->setField("inDither", value);
}

bool android::graphics::BitmapFactory::Options::inInputShareable() {
    return this->getField<bool>("inInputShareable");
}

void android::graphics::BitmapFactory::Options::inInputShareable(bool value) {
    this->setField("inInputShareable", value);
}

bool android::graphics::BitmapFactory::Options::inJustDecodeBounds() {
    return this->getField<bool>("inJustDecodeBounds");
}

void android::graphics::BitmapFactory::Options::inJustDecodeBounds(bool value) {
    this->setField("inJustDecodeBounds", value);
}

bool android::graphics::BitmapFactory::Options::inMutable() {
    return this->getField<bool>("inMutable");
}

void android::graphics::BitmapFactory::Options::inMutable(bool value) {
    this->setField("inMutable", value);
}

bool android::graphics::BitmapFactory::Options::inPreferQualityOverSpeed() {
    return this->getField<bool>("inPreferQualityOverSpeed");
}

void android::graphics::BitmapFactory::Options::inPreferQualityOverSpeed(bool value) {
    this->setField("inPreferQualityOverSpeed", value);
}

android::graphics::ColorSpace android::graphics::BitmapFactory::Options::inPreferredColorSpace() {
    return this->getField<ColorSpace>("inPreferredColorSpace");
}

void android::graphics::BitmapFactory::Options::inPreferredColorSpace(ColorSpace value) {
    this->setField("inPreferredColorSpace", value);
}

android::graphics::Bitmap::Config android::graphics::BitmapFactory::Options::inPreferredConfig() {
    return this->getField<Bitmap::Config>("inPreferredConfig");
}

void android::graphics::BitmapFactory::Options::inPreferredConfig(Bitmap::Config value) {
    this->setField("inPreferredConfig", value);
}

#endif  //__ANDROID__
