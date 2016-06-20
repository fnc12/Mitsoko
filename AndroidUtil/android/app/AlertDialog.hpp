
#pragma once

#include "Dialog.hpp"
#include "Viper/AndroidUtil/android/content/Context.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"
#include <functional>
#include <map>
#include "Viper/AndroidUtil/android/content/DialogInterface.hpp"
#include "Viper/AndroidUtil/android/view/View.hpp"

namespace android{
    namespace app{
        struct AlertDialog:public Dialog{
            using Dialog::Dialog;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/app/AlertDialog");
            
            void show(){
                this->sendMessage<void>("show");
            }
            
            struct Builder:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/app/AlertDialog$Builder");
                
                typedef std::function<void(content::DialogInterface,int)> OnClickCallback;
                typedef std::map<int,OnClickCallback> OnClickMap;
                STATIC_VAR(OnClickMap, onClickMap, {});
                
                static Builder create(const content::Context &context){
                    return std::move(java::lang::Object::create<Builder>(context));
                }
                
                /**
                 *  Fucntion called from NI.cpp when dialogOnClick happens.
                 *  Must not be called directly.
                 */
                static void alertDialogClickListener_onClick(int id,jobject dialogInterface,int which){
                    auto it=onClickMap().find(id);
                    if(it != onClickMap().end()){
                        it->second(dialogInterface,which);
                        onClickMap().erase(it);
                    }
                }
                
                AlertDialog create(){
                    return std::move(this->sendMessage<AlertDialog>("create"));
                }
                
                Builder& setTitle(const std::string &title){
                    auto str=java::lang::String::create(title);
                    return this->setTitle(str);
                }
                
                Builder& setTitle(const java::lang::CharSequence &title){
//                    LOGI("(CharSequence)title = %p",title.handle);
                    this->sendMessage<Builder>("setTitle",title);
                    return *this;
                }
                
                Builder& setPositiveButton(const std::string &text,
                                           std::function<void(content::DialogInterface,int)> cb)
                {
                    auto t=java::lang::String::create(text);
                    return this->setPositiveButton(t,cb);
                }
                
                Builder& setPositiveButton(const java::lang::CharSequence &text,
                                           std::function<void(content::DialogInterface,int)> cb)
                {
                    auto classSignature=java::lang::JNI::appNamespace()+"/EventHandlers$AlertDialogClickListener";
                    auto callbackObject=java::lang::Object::create(classSignature);
                    auto callbackId=callbackObject.getField<int>("mId");
                    onClickMap().insert({callbackId,cb});
                    auto l=(android::content::DialogInterface::OnClickListener)callbackObject;
                    this->sendMessage<Builder>("setPositiveButton",text,l);
                    return *this;
                }
                
                Builder& setNegativeButton(const std::string &text,
                                           std::function<void(content::DialogInterface,int)> cb)
                {
                    auto t=java::lang::String::create(text);
                    return this->setNegativeButton(t,cb);
                }
                
                Builder& setNegativeButton(const java::lang::CharSequence &text,
                                           std::function<void(content::DialogInterface,int)> cb)
                {
                    auto classSignature=java::lang::JNI::appNamespace()+"/EventHandlers$AlertDialogClickListener";
                    auto callbackObject=java::lang::Object::create(classSignature);
                    auto callbackId=callbackObject.getField<int>("mId");
                    onClickMap().insert({callbackId,cb});
                    auto l=(android::content::DialogInterface::OnClickListener)callbackObject;
                    this->sendMessage<Builder>("setNegativeButton",text,l);
                    return *this;
                }
                
                Builder& setView(const android::view::View &view){
                    this->sendMessage<Builder>("setView",view);
                    return *this;
                }
            };
#endif
        };
    }
}
