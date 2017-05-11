//
//  ViewGroup.cpp
//  Jako
//
//  Created by John Zakharov on 05.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ViewGroup.hpp"

#ifdef __ANDROID__

const std::string android::view::ViewGroup::signature = "android/view/ViewGroup";

const std::string android::view::ViewGroup::LayoutParams::signature = "android/view/ViewGroup$LayoutParams";

const std::string android::view::ViewGroup::MarginLayoutParams::signature = "android/view/ViewGroup$MarginLayoutParams";

template<>
void android::view::View::setLayoutParams<android::view::ViewGroup::LayoutParams>(const android::view::ViewGroup::LayoutParams &params){
    this->sendMessage<void>("setLayoutParams",params);
}

android::view::ViewGroup::LayoutParams android::view::ViewGroup::LayoutParams::create(int width, int height) {
    return java::lang::Object::create<LayoutParams>(width, height);
}

int android::view::ViewGroup::LayoutParams::MATCH_PARENT(){
    if(java::lang::Class cls = java::lang::Class::find<LayoutParams>()){
        auto res = cls.getStaticField<int>("MATCH_PARENT");
//        java::lang::JNI::Env()->DeleteLocalRef(jobject(cls.handle));
        return res;
    }else{
        return -1;
    }
}

int android::view::ViewGroup::LayoutParams::WRAP_CONTENT(){
    if(java::lang::Class cls=java::lang::Class::find<LayoutParams>()){
        auto res = cls.getStaticField<int>("WRAP_CONTENT");
//        java::lang::JNI::Env()->DeleteLocalRef(jobject(cls.handle));
        return res;
    }else{
        return -1;
    }
}

void android::view::ViewGroup::removeAllViews() {
    this->sendMessage<void>("removeAllViews");
}

void android::view::ViewGroup::addView(const android::view::View &v) {
    this->sendMessage<void>("addView", v);
}

#endif
