//
//  View.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "View.hpp"

#ifdef __ANDROID__

const std::string android::view::View::signature = "android/view/View";

const std::string android::view::View::OnClickListener::signature = "android/view/View$OnClickListener";

android::view::View::OnClickMap android::view::View::onClickMap;

android::view::View::DisposablesMap android::view::View::disposablesMap;

void android::view::View::onClick(int id,android::view::View v){
    auto it=onClickMap.find(id);
    if(it != onClickMap.end()){
        it->second(v);
    }else{
        std::cerr<<"callback not found with id "<<id<<std::endl;
    }
}

void android::view::View::setOnClickListener(OnClick cb,const Mitsoko::Disposable &disposable){
    OnClickListener l;
    if(onClick){
        auto classSignature="kz/outlawstudio/viper/EventHandlers$ViewOnClickListener";
        auto callbackObject=java::lang::Object::create(classSignature);
        auto callbackId=callbackObject.getField<int>("mId");
        onClickMap.insert({callbackId,cb});
        l=(OnClickListener)callbackObject;
        disposablesMap.insert({disposable.id,callbackId});
    }
    this->sendMessage<void>("setOnClickListener",l);
}

auto android::view::View::findViewById(int id)->View{
    return this->sendMessage<View>("findViewById",id);
}

auto android::view::View::findViewById(const std::string &idString,const content::Context &context)->View{
    if(auto java_env=java::lang::JNI::Env()){
        auto niClazz=java::lang::Class::find("kz/outlawstudio/viper/NI");
        auto signature=java::lang::Object::generateMethodSignature<int,content::Context,java::lang::String,java::lang::String>();
        auto methodId=java_env->GetStaticMethodID(niClazz,"getResourseId",signature.c_str());
        auto resourseId=java::lang::String::create(idString);
        auto folderName=java::lang::String::create("id");
        auto resID=java_env->CallStaticIntMethod(niClazz,
                                                 methodId,
                                                 context.handle,
                                                 resourseId.handle,
                                                 folderName.handle);
        return this->findViewById(resID);
    }else{
        return {};
    }
}

void android::view::View::setVisibility(int visibility){
    this->sendMessage<void>("setVisibility",visibility);
}

void android::view::View::setEnabled(bool enabled){
    this->sendMessage<void>("setEnabled",enabled);
}

bool android::view::View::isEnabled(){
    return this->sendMessage<bool>("isEnabled");
}

int android::view::View::getWidth(){
    return this->sendMessage<int>("getWidth");
}

void android::view::View::setBackgroundColor(int color) {
    this->sendMessage<void>("setBackgroundColor", color);
}

int android::view::View::getHeight(){
    return this->sendMessage<int>("getHeight");
}

int android::view::View::VISIBLE() {
    if(java::lang::Class cls = java::lang::Class::find<View>()) {
        return cls.getStaticField<int>("VISIBLE");
    }else{
        return -1;
    }
}

int android::view::View::INVISIBLE() {
    if(java::lang::Class cls = java::lang::Class::find<View>()) {
        return cls.getStaticField<int>("INVISIBLE");
    }else{
        return -1;
    }
}

int android::view::View::GONE(){
    if(java::lang::Class cls=java::lang::Class::find<View>()){
        return cls.getStaticField<int>("GONE");
    }else{
        return -1;
    }
}

android::os::IBinder android::view::View::getWindowToken() {
    return this->sendMessage<android::os::IBinder>("getWindowToken");
}

android::view::View android::view::View::getRootView() {
    return this->sendMessage<View>("getRootView");
}

#endif  //__ANDROID__
