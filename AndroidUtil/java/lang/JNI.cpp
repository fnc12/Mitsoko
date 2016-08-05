//
//  JNI.cpp
//  Jako
//
//  Created by John Zakharov on 05.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "JNI.hpp"

#ifdef __ANDROID__

std::string java::lang::JNI::appId;

std::string java::lang::JNI::appNamespace;

java::lang::JNI::JNIEnvMap java::lang::JNI::envMap;

std::mutex java::lang::JNI::envMapMutex;

java::lang::JNI::JNI(JNIEnv *env){
    if(!Env()){
        insertEnv(env);
        this->hasValue=true;
    }
}

java::lang::JNI::~JNI(){
    if(this->hasValue){
        removeEnv();
        this->hasValue=false;
    }
}

JNIEnv* java::lang::JNI::Env(){
    JNIEnv *res=nullptr;
    
    envMapMutex.lock();
    const auto threadId=std::this_thread::get_id();
    const auto it=envMap.find(threadId);
    if(it!=envMap.end()){
        res=it->second;
    }
    envMapMutex.unlock();
    
    return res;
}

void java::lang::JNI::insertEnv(JNIEnv *env){
    auto threadId=std::this_thread::get_id();
    
    envMapMutex.lock();
    envMap.insert({threadId,env});
    envMapMutex.unlock();
}

void java::lang::JNI::removeEnv(){
    auto threadId=std::this_thread::get_id();
    
    envMapMutex.lock();
    const auto it=envMap.find(threadId);
    if(it != envMap.end()){
        envMap.erase(it);
    }
    envMapMutex.unlock();
}

#endif
