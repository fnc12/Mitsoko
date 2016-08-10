//
//  Dispatch.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Dispatch.hpp"

#ifdef __ANDROID__

using namespace java::lang;
using namespace android::os;

Viper::Dispatch::Callbacks Viper::Dispatch::callbacks;

std::mutex Viper::Dispatch::callbacksMutex;

std::mutex Viper::Dispatch::mainThreadHandlersMutex;

int Viper::Dispatch::callbackId=0;

Handler Viper::Dispatch::mainThreadHandler;

void Viper::Dispatch::postCallback(int callbackId,bool isMainThread){
    std::function<void()> f;
    
    callbacksMutex.lock();
    auto it=callbacks.find(callbackId);
    if(it!=callbacks.end()){
        f=it->second;
        callbacks.erase(it);
    }
    callbacksMutex.unlock();
    
    if(f){
        f();
    }else{
        std::cerr<<"callback not found with id "<<callbackId<<std::endl;
    }
}

void Viper::Dispatch::initMainThreadHandler(){
    if(auto handler=Handler::create()){
        auto globalHandler=java::lang::JNI::Env()->NewGlobalRef((jobject)handler.handle);
        mainThreadHandler=globalHandler;
    }else{
        std::cerr<<"handler is null"<<std::endl;
    }
}
#endif

void Viper::Dispatch::onBackground(std::function<void()> functionPointer){
#ifdef __APPLE__
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        functionPointer();
    });
#else
    if(auto java_env=java::lang::JNI::Env()){
        callbacksMutex.lock();
        const auto cId=callbackId++;
        callbacks.insert({cId,functionPointer});
        callbacksMutex.unlock();
        
        auto backgroundRunnableClass=java_env->FindClass("kz/outlawstudio/viper/BackgroundRunnable");
        auto ctor=java_env->GetMethodID(backgroundRunnableClass,"<init>",Object::generateMethodSignature<void,int>().c_str());
        java::lang::Runnable backgroundRunnable = java_env->NewObject(backgroundRunnableClass, ctor,jint(cId));
        auto thread=Thread::create(backgroundRunnable);
        thread.start();
    }else{
        std::cerr<<"java::lang::JNI::Env is null"<<std::endl;
    }
#endif
}

void Viper::Dispatch::onMainThread(std::function<void()> functionPointer){
#ifdef __APPLE__
    dispatch_async(dispatch_get_main_queue(), ^{
        functionPointer();
    });
#else
    if(auto java_env=java::lang::JNI::Env()){
        
        callbacksMutex.lock();
        const auto cId=callbackId++;
        callbacks.insert({cId,functionPointer});
        callbacksMutex.unlock();
        
        auto backgroundRunnableClass=java_env->FindClass("kz/outlawstudio/viper/BackgroundRunnable");
        auto ctor=java_env->GetMethodID(backgroundRunnableClass,"<init>",Object::generateMethodSignature<void,int>().c_str());
        Runnable backgroundRunnable = java_env->NewObject(backgroundRunnableClass, ctor,jint(cId));
        mainThreadHandler.post(backgroundRunnable);
        
    }else{
        std::cout<<"java::lang::JNI::Env is null"<<std::endl;
    }
#endif
}

void Viper::operator--(std::function<void()> f){
    Viper::Dispatch::onMainThread(f);
}

void Viper::operator++(std::function<void()> f){
    Viper::Dispatch::onBackground(f);
}


