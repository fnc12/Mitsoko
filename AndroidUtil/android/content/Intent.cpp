//
//  Intent.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Intent.hpp"

#ifdef __ANDROID__

//const std::string android::content::Intent::signature="android/content/Intent";

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
    if(java::lang::Class cls=java::lang::Class::find<Intent>()){
        return cls.getStaticField<java::lang::String>("ACTION_CALL");
    }else{
        return {};
    }
}

android::net::Uri android::content::Intent::getData(){
    return this->sendMessage<android::net::Uri>("getData");
}

android::os::Bundle android::content::Intent::getExtras(){
    return this->sendMessage<android::os::Bundle>("getExtras");
}

auto android::content::Intent::putExtra(const std::string &name,const std::string &value)->Intent&{
    auto j_name=java::lang::String::create(name);
    auto j_value=java::lang::String::create(value);
    this->sendMessage<Intent>("putExtra",j_name,j_value);
    return *this;
}

auto android::content::Intent::setData(const android::net::Uri &data)->Intent&{
    this->sendMessage<Intent>("setData",data);
    return *this;
}

#endif  //__ANDROID__
