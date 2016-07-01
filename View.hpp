//
//  View.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef View_h
#define View_h

#include <memory>
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"
#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include "Disposable.hpp"
#include "rapidjson/Document.h"
#include "ViewPresenterIF.hpp"
#include "ImageCache.hpp"

#define VIEW_DECL(module) struct View:public Viper::View<module::EventHandler, module::UserInterface>,Selfish<View>

/**
 *  Used fo simplifying client member references declaration.
 */
#ifdef __APPLE__
#define FIELD_DECL(type,name) type name(){return NS::Object::sendMessage<Handle>(self.handle,#name);}
#else
#define FIELD_DECL(type,name) type name(){return java::lang::Object(self.handle).getField<type>(#name);}
#endif

namespace Viper{
    struct ViewBase{
        const void *handle;
        
        ViewBase(decltype(handle)handle_):handle(handle_){};
        
        virtual ~ViewBase(){
            
            //  unregister all table- or listview adapters hosted by this view..
            for(auto adapterId:this->adapterIds){
                TableListAdapter::registerAdapter(adapterId, {});
            }
            this->adapterIds.clear();
        }
        
        virtual void willAppear()=0;
        virtual void didAppear()=0;
        virtual void willDisappear()=0;
        
        typedef std::map<std::string,std::string> Arguments;
        
        void messageReceived(int messageCode,std::string jsonArguments){
            Arguments arguments;
            if(jsonArguments.length()){
                rapidjson::Document d;
                d.Parse(jsonArguments.c_str());
                if(d.IsObject()){
                    for(auto it=d.MemberBegin();it!=d.MemberEnd();++it){
                        if(it->name.IsString()&&it->value.IsString()){
                            arguments.insert({it->name.GetString(),it->value.GetString()});
                        }
                    }
                }
            }
            this->messageReceived(messageCode,std::move(arguments));
        }
        
//#ifdef __ANDROID__
        virtual void onActivityResult(int requestCode,int resultCode, android::content::Intent data){
            //..
        }
//#endif
        
        virtual void messageReceived(int messageCode,Arguments arguments){}
        
        std::string arguments(){
#ifdef __APPLE__
//            auto argumentsString=reinterpret_cast<const void*(*)(const void*,SEL)>(objc_msgSend)(this->handle,sel_getUid("arguments"));
            NS::String argumentsString=NS::Object(this->handle).sendMessage<decltype(handle)>("arguments");
//            return reinterpret_cast<const char*(*)(const void*,SEL)>(objc_msgSend)(argumentsString,sel_getUid("UTF8String"));
            return argumentsString.UTF8String();
#else
#ifdef __ANDROID__
            if(auto java_env=JNI::Env()){
                if(auto clazz=java_env->GetObjectClass(jobject(this->handle))){
                    if(auto field = java_env->GetFieldID(clazz, "arguments", ("L"+java::lang::String::signature()+";").c_str())){
                        if(java::lang::String str=java_env->GetObjectField(jobject(this->handle), field)){
                            return str.c_str();
                        }else{
                            return {};
                        }
                    }else{
                        return {};
                    }
                }else{
                    return {};
                }
            }else{
                return {};
            }
#else
#error "Unknown OS"
#endif
#endif
        }
        
    protected:
        
        /**
         *  Adapter ids of table- or listviews in current view. If you want its adapters to be removed
         *  from memory properly you have to either setAdapter({}) or add adapter id into this
         *  vector and it will be cleared in destructor. You can obtain adapter id as a returned value
         *  from *setAdapter* function in **UI::TableView** or **android::widget::ListView**.
         */
        std::vector<TableListAdapter::AdapterId> adapterIds;
    };
    
    //  base class for view..
    template<class EH,class UI>
    struct View:public ViewBase,public Disposable,public UI{
        std::shared_ptr<EH> eventHandler;
        
        using ViewBase::ViewBase;
        
        virtual void init(){}
        
        virtual void willAppear() override{
            this->eventHandler->viewWillAppear();
        }
        
        virtual void didAppear() override{
            this->eventHandler->viewDidAppear();
        }
        
        virtual void willDisappear() override{
            this->eventHandler->viewWillDisappear();
        }
        
        template<class T>
        void setEventHandler(std::shared_ptr<T> ptr){
            this->eventHandler=std::dynamic_pointer_cast<EH>(ptr);
        }
        
        virtual void dispose() override{
            this->Disposable::dispose();
            this->eventHandler=nullptr;
        }
    protected:
        typedef View<EH,UI> V;
    };
}

#endif /* View_h */
