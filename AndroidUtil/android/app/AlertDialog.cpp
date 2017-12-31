//
//  AlertDialog.cpp
//  Groozim
//
//  Created by John Zakharov on 16.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "AlertDialog.hpp"

#ifdef __ANDROID__

const std::string android::app::AlertDialog::signature = "android/app/AlertDialog";

const std::string android::app::AlertDialog::Builder::signature = "android/app/AlertDialog$Builder";

android::app::AlertDialog::Builder::OnClickMap android::app::AlertDialog::Builder::onClickMap;

void android::app::AlertDialog::show(){
    this->sendMessage<void>("show");
}

auto android::app::AlertDialog::Builder::create(const content::Context &context)->Builder{
    return std::move(java::lang::Object::create<Builder>(context));
}

void android::app::AlertDialog::Builder::alertDialogClickListener_onClick(int id,jobject dialogInterface,int which){
    auto it = onClickMap.find(id);
    if(it != onClickMap.end()){
        it->second(dialogInterface, which);
        onClickMap.erase(it);
    }
}

auto android::app::AlertDialog::Builder::create()->AlertDialog{
    return std::move(this->sendMessage<AlertDialog>("create"));
}

auto android::app::AlertDialog::Builder::setItems(const std::vector<std::string> &items,OnClickCallback cb) -> Builder& {
    auto jItems = java::lang::Array<java::lang::CharSequence>::create(int(items.size()), {});
    for(size_t i=0;i<items.size();++i){
        const auto &item = items[i];
        auto str = java::lang::String::create(item);
        jItems[i] = str;
    }
    auto classSignature = "kz/outlawstudio/viper/EventHandlers$AlertDialogClickListener";
    auto callbackObject = java::lang::Object::create(classSignature);
    auto callbackId = callbackObject.getField<int>("mId");
    onClickMap.insert({callbackId, cb});
    auto l = (android::content::DialogInterface::OnClickListener)callbackObject;
    this->sendMessage<Builder>("setItems", jItems, l);
    return *this;
}

auto android::app::AlertDialog::Builder::setMessage(const std::string &title)->Builder&{
    auto t = java::lang::String::create(title);
    return this->setMessage(t);
}

auto android::app::AlertDialog::Builder::setMessage(const java::lang::CharSequence &title)->Builder&{
    this->sendMessage<Builder>("setMessage", title);
    return *this;
}

auto android::app::AlertDialog::Builder::setTitle(const std::string &title)->Builder&{
    auto str = java::lang::String::create(title);
    return this->setTitle(str);
}

auto android::app::AlertDialog::Builder::setTitle(const java::lang::CharSequence &title)->Builder&{
    this->sendMessage<Builder>("setTitle", title);
    return *this;
}

auto android::app::AlertDialog::Builder::setPositiveButton(const std::string &text,OnClickCallback cb)->Builder&{
    auto t = java::lang::String::create(text);
    return this->setPositiveButton(t, cb);
}

auto android::app::AlertDialog::Builder::setPositiveButton(const java::lang::CharSequence &text,OnClickCallback cb)->Builder&{
    android::content::DialogInterface::OnClickListener l;
    if(cb){
        auto classSignature = "kz/outlawstudio/viper/EventHandlers$AlertDialogClickListener";
        auto callbackObject = java::lang::Object::create(classSignature);
        auto callbackId = callbackObject.getField<int>("mId");
        onClickMap.insert({callbackId, cb});
        l = (android::content::DialogInterface::OnClickListener)callbackObject;
    }
    this->sendMessage<Builder>("setPositiveButton", text, l);
    return *this;
}

auto android::app::AlertDialog::Builder::setNegativeButton(const std::string &text,OnClickCallback cb)->Builder&{
    auto t=java::lang::String::create(text);
    return this->setNegativeButton(t,cb);
}

auto android::app::AlertDialog::Builder::setNegativeButton(const java::lang::CharSequence &text,OnClickCallback cb)->Builder&{
    android::content::DialogInterface::OnClickListener l;
    if(cb){
        auto classSignature="kz/outlawstudio/viper/EventHandlers$AlertDialogClickListener";
        auto callbackObject=java::lang::Object::create(classSignature);
        auto callbackId=callbackObject.getField<int>("mId");
        onClickMap.insert({callbackId,cb});
        l=(android::content::DialogInterface::OnClickListener)callbackObject;
    }
    this->sendMessage<Builder>("setNegativeButton",text,l);
    return *this;
}

auto android::app::AlertDialog::Builder::setView(const android::view::View &view)->Builder&{
    this->sendMessage<Builder>("setView",view);
    return *this;
}

#endif  //__ANDROID__
