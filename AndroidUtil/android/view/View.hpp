
#pragma once

#include "Viper/AndroidUtil/java/lang/Class.hpp"
#include "Viper/AndroidUtil/android/content/Context.hpp"
#include <functional>
#include <map>
#include "Viper/Disposable.hpp"

namespace android{
    namespace view{
        
        struct View:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/view/View");
            
            typedef std::function<void(Handle)> OnClick;
            
            typedef std::map<int,OnClick> OnClickMap;
            STATIC_VAR(OnClickMap, onClickMap, {});
            
            typedef std::map<Viper::Disposable::Id,int> DisposablesMap;
            STATIC_VAR(DisposablesMap, disposablesMap, {});
            
            struct OnClickListener:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/view/View$OnClickListener");
            };
            
            static void onClick(int id,android::view::View v){
                auto it=onClickMap().find(id);
                if(it != onClickMap().end()){
                    it->second(v);
                }else{
                    std::cerr<<"callback not found with id "<<id<<std::endl;
                }
            }
            
            void setOnClickListener(OnClick cb,const Viper::Disposable &disposable){
                OnClickListener l;
                if(onClick){
                    auto classSignature="kz/outlawstudio/viper/EventHandlers$ViewOnClickListener";
                    auto callbackObject=java::lang::Object::create(classSignature);
                    auto callbackId=callbackObject.getField<int>("mId");
                    onClickMap().insert({callbackId,cb});
                    l=(OnClickListener)callbackObject;
                    disposablesMap().insert({disposable.id,callbackId});
                }
                this->sendMessage<void>("setOnClickListener",l);
            }
            
            /**
             *  Implemented in ViewGroup.hpp"
             */
            template<class T>
            void setLayoutParams(const T &params);
            
            View findViewById(int id){
                return this->sendMessage<View>("findViewById",id);
            }
            
            /**
             *  This function actually doesn't exist in SDK but it is created
             *  to simplify developers finding a subview by string identifier from xml-file.
             *  =========
             *  Also it's body contains call to 'getResourseId' static function call instead of
             *  android native context.getResources.getIdentifier("view_id","id",context.getPackageName());.
             *  This is done because calling context.getResources.getIdentifier from C++ always returns
             *  incorrect id. The reason is still unknown so I decided to transfer this logic into
             *  client side. If you know the reason why context.getResources.getIdentifier doesn't work
             *  correctly please contact me fnc12@me.com. Thanks
             */
            View findViewById(const std::string &idString,const content::Context &context){
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
            
            void setVisibility(int visibility){
                this->sendMessage<void>("setVisibility",visibility);
            }
            
            void setEnabled(bool enabled){
                this->sendMessage<void>("setEnabled",enabled);
            }
            
            bool isEnabled(){
                return this->sendMessage<bool>("isEnabled");
            }
            
            int getWidth(){
                return this->sendMessage<int>("getWidth");
            }
            
            int getHeight(){
                return this->sendMessage<int>("getHeight");
            }
            
            static int VISIBLE(){
                if(java::lang::Class cls=java::lang::Class::find<View>()){
                    return cls.getStaticField<int>("VISIBLE");
                }else{
                    return -1;
                }
            }
            
            static int GONE(){
                if(java::lang::Class cls=java::lang::Class::find<View>()){
                    return cls.getStaticField<int>("GONE");
                }else{
                    return -1;
                }
            }
#endif
        };
    }
}
