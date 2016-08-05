//
//  Dispatch.hpp
//  Jako
//
//  Created by John Zakharov on 20.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef Dispatch_h
#define Dispatch_h

#ifdef __APPLE__
//    #ifdef __OBJC__
        #include <dispatch/dispatch.h>
//    #endif
#else
    #include "AndroidUtil/AndroidUtil.hpp"
#endif
#include <functional>
#include <map>
#include <mutex>
#include <vector>

namespace Viper{
#ifdef __ANDROID__
    using namespace java::lang;
    using namespace android::os;
#endif
    struct Dispatch{
#ifdef __ANDROID__
        STATIC_VAR(jobject, frontActivity, nullptr);
    protected:
        typedef std::map<int,std::function<void()>> Callbacks;
        STATIC_VAR(Callbacks, callbacks, {});
        static std::mutex& callbacksMutex(){
            static std::mutex res;
            return res;
        }
        static std::mutex& mainThreadHandlersMutex(){
            static std::mutex res;
            return res;
        }
        STATIC_VAR(int, callbackId, 0);
        STATIC_VAR(Handler, mainThreadHandler, {});
        STATIC_VAR(std::vector<jobject>, mainThreadHandlers, {});
    public:
        static void postCallback(int callbackId,bool isMainThread){
            std::function<void()> f;
            
            callbacksMutex().lock();
            auto it=callbacks().find(callbackId);
            if(it!=callbacks().end()){
                f=it->second;
                callbacks().erase(it);
            }
            callbacksMutex().unlock();
            /*if(isMainThread){
//                handlerIsBusy()=false;
            }*/
            
            if(f){
                f();
            }else{
                std::cout<<"callback not found with id "<<callbackId<<std::endl;
            }
        }
        
        /**
          * Creates android.os.Handler object. Should be called once
          * and from main thread only before any 'onMainThread' call.
          */
        static void initMainThreadHandler(){
            if(auto handler=Handler::create()){
                auto globalHandler=java::lang::JNI::Env()->NewGlobalRef((jobject)handler.handle);
                mainThreadHandler()=globalHandler;
            }else{
                std::cout<<"handler is null"<<std::endl;
            }
        }
#endif
    public:
        static void onBackground(std::function<void()> functionPointer){
#ifdef __APPLE__
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                functionPointer();
            });
#else
            if(auto java_env=java::lang::JNI::Env()){
                callbacksMutex().lock();
//                LOGI("inserting callback for background");
                const auto cId=callbackId()++;
                callbacks().insert({cId,functionPointer});
//                LOGI("callback on background inserted %d",cId);
                callbacksMutex().unlock();
                
                auto backgroundRunnableClass=java_env->FindClass("kz/outlawstudio/viper/BackgroundRunnable");
//                auto backgroundRunnableClass=java::lang::Class::find(java::lang::JNI::appNamespace()+"/BackgroundRunnable");
//                auto niClazz=java::lang::Class::find(java::lang::JNI::appNamespace()+"/NI");
                auto ctor=java_env->GetMethodID(backgroundRunnableClass,"<init>",Object::generateMethodSignature<void,int>().c_str());
                java::lang::Runnable backgroundRunnable = java_env->NewObject(backgroundRunnableClass, ctor,jint(cId));
                auto thread=Thread::create(backgroundRunnable);
                thread.start();
            }else{
                std::cout<<"java::lang::JNI::Env is null"<<std::endl;
            }
#endif
        }
        
        static void onMainThread(std::function<void()> functionPointer){
#ifdef __APPLE__
            dispatch_async(dispatch_get_main_queue(), ^{
                functionPointer();
            });
#else
            if(auto java_env=java::lang::JNI::Env()){
                
                callbacksMutex().lock();
                const auto cId=callbackId()++;
                callbacks().insert({cId,functionPointer});
                callbacksMutex().unlock();

//                auto backgroundRunnableClass=java_env->FindClass("kz/outlawstudio/groozim/BackgroundRunnable");
//                auto backgroundRunnableClass=java::lang::Class::find(java::lang::JNI::appNamespace()+"/BackgroundRunnable");
                auto backgroundRunnableClass=java_env->FindClass("kz/outlawstudio/viper/BackgroundRunnable");
                auto ctor=java_env->GetMethodID(backgroundRunnableClass,"<init>",Object::generateMethodSignature<void,int>().c_str());
                Runnable backgroundRunnable = java_env->NewObject(backgroundRunnableClass, ctor,jint(cId));
                mainThreadHandler().post(backgroundRunnable);
                
            }else{
                std::cout<<"java::lang::JNI::Env is null"<<std::endl;
            }
#endif
        }
    };
    
    //  syntax sugar..
    inline void operator--(std::function<void()> f){
        Viper::Dispatch::onMainThread(f);
    }
    
    inline void operator++(std::function<void()> f){
        Viper::Dispatch::onBackground(f);
    }
}

#endif /* Dispatch_h */
