//
//  ImageView.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ImageView.hpp"

#ifdef __ANDROID__

//const std::string android::widget::ImageView::signature="android/widget/ImageView";

void android::widget::ImageView::setImageResource(const std::string &resName,const content::Context &context){
    if(auto java_env=java::lang::JNI::Env()){
        auto niClazz=java::lang::Class::find("kz/outlawstudio/viper/NI");
        auto signature=java::lang::Object::generateMethodSignature<int,content::Context,java::lang::String,java::lang::String>();
        auto methodId=java_env->GetStaticMethodID(niClazz,"getResourseId",signature.c_str());
        auto resourseId=java::lang::String::create(resName);
        auto folderName=java::lang::String::create("drawable");
        auto resID=java_env->CallStaticIntMethod(niClazz,methodId,
                                                 context.handle,
                                                 resourseId.handle,
                                                 folderName.handle);
        this->setImageResource(resID);
    }
}

void android::widget::ImageView::setImageResource(int resId){
    this->sendMessage<void>("setImageResource",resId);
}

void android::widget::ImageView::setImageBitmap(const android::graphics::Bitmap &bm){
    this->sendMessage<void>("setImageBitmap",bm);
}

#endif  //__ANDROID__
