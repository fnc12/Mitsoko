//
//  Intent.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Intent.hpp"
#include "Mitsoko/AndroidUtil/java/lang/Class.hpp"

#ifdef __ANDROID__

const std::string android::content::Intent::signature = "android/content/Intent";

auto android::content::Intent::create(const Context &context,const java::lang::Class &cls)->Intent{
    return std::move(java::lang::Object::create<Intent>(context,cls));
}

auto android::content::Intent::create(const java::lang::String &action,const android::net::Uri &uri)->Intent{
    return std::move(java::lang::Object::create<Intent>(action,uri));
}

auto android::content::Intent::create(const java::lang::String &action)->Intent{
    return std::move(java::lang::Object::create<Intent>(action));
}

java::lang::String android::content::Intent::ACTION_PICK(){
    if(java::lang::Class cls=java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("ACTION_PICK");
    }else{
        return {};
    }
}

java::lang::String android::content::Intent::ACTION_CALL(){
    if(java::lang::Class cls = java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("ACTION_CALL");
    }else{
        return {};
    }
}

java::lang::String android::content::Intent::ACTION_SEND() {
    if(java::lang::Class cls = java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("ACTION_SEND");
    }else{
        return {};
    }
}

java::lang::String android::content::Intent::EXTRA_EMAIL() {
    if(java::lang::Class cls = java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("EXTRA_EMAIL");
    }else{
        return {};
    }
}

java::lang::String android::content::Intent::EXTRA_SUBJECT() {
    if(java::lang::Class cls = java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("EXTRA_SUBJECT");
    }else{
        return {};
    }
}

java::lang::String android::content::Intent::EXTRA_TEXT() {
    if(java::lang::Class cls = java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("EXTRA_TEXT");
    }else{
        return {};
    }
}

auto android::content::Intent::createChooser(const Intent &target, const std::string &title) -> Intent {
    if(auto java_env = java::lang::JNI::Env()){
        auto t = java::lang::String::create(title);
//        auto clazz = java_env->FindClass(signature().c_str());
        java::lang::Class clazz = java::lang::Class::find<Intent>();
        /*auto methodSignature = generateMethodSignature<Intent, Intent, java::lang::CharSequence>();
        auto mid = java_env->GetStaticMethodID(clazz,
                                               "createChooser",
                                               methodSignature.c_str());
        return java_env->CallStaticObjectMethod(clazz,
                                                mid,
                                                target.handle,
                                                t.handle);*/
        return clazz.callStaticFunc<Intent>("createChooser", target, t);
    }else{
        return {};
    }
}

android::content::Intent& android::content::Intent::setType(const std::string &type) {
    auto t = java::lang::String::create(type);
    this->sendMessage<android::content::Intent>("setType", t);
    return *this;
}

android::net::Uri android::content::Intent::getData(){
    return this->sendMessage<android::net::Uri>("getData");
}

android::os::Bundle android::content::Intent::getExtras(){
    return this->sendMessage<android::os::Bundle>("getExtras");
}

auto android::content::Intent::putExtra(const std::string &name,const std::string &value)->Intent&{
    auto j_name = java::lang::String::create(name);
    auto j_value = java::lang::String::create(value);
    this->sendMessage<Intent>("putExtra", j_name, j_value);
    return *this;
}

android::content::Intent& android::content::Intent::putExtra(const std::string &name, const std::vector<std::string> &value) {
    auto j_name = java::lang::String::create(name);
    auto jItems = java::lang::Array<java::lang::String>::create(int(value.size()), {});
    for(auto i = 0; i < value.size(); ++i) {
        auto &v = value[i];
        auto str = java::lang::String::create(v);
        jItems[i] = str;
    }
    this->sendMessage<Intent>("putExtra", j_name, jItems);
}

auto android::content::Intent::setData(const android::net::Uri &data)->Intent&{
    this->sendMessage<Intent>("setData",data);
    return *this;
}

#endif  //__ANDROID__
