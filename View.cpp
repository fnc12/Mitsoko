//
//  View.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "View.hpp"
//#include "rapidjson/Document.h"

#include <iostream>

using std::cout;
using std::endl;

//Viper::ViewBase::ViewBase(decltype(handle)handle_):handle(handle_){};

Viper::ViewBase::~ViewBase(){
    
    //  unregister all table- or listview adapters hosted by this view..
    for(auto adapterId:this->adapterIds){
        TableListAdapter::registerAdapter(adapterId, {});
    }
    this->adapterIds.clear();
}

/*void Viper::ViewBase::messageReceived(int messageCode,std::string jsonArguments){
    Arguments arguments;
    LOGI("jsonArguments = *%s*",jsonArguments.c_str());
    LOGI("jsonArguments.length() = %ld",jsonArguments.length());
    if(jsonArguments.length()){
        rapidjson::Document d;
        d.Parse(jsonArguments.c_str());
        if(d.IsObject()){
            for(auto it=d.MemberBegin();it!=d.MemberEnd();++it){
                if(it->name.IsString() && it->value.IsString()){
                    arguments.insert({it->name.GetString(),it->value.GetString()});
                    cout << "name = " << it->name.GetString() << ", value = " << it->value.GetString() << endl;
                }
            }
        }else{
            LOGI("d is not an object (%s)", jsonArguments.c_str());
        }
    }
    this->messageReceived(messageCode,std::move(arguments));
}*/

void Viper::ViewBase::onActivityResult(int requestCode,int resultCode, android::content::Intent data){
    //..
}

/*std::string Viper::ViewBase::arguments(){
#ifdef __APPLE__
    NS::String argumentsString=NS::Object(this->handle).sendMessage<decltype(handle)>("arguments");
    return argumentsString.UTF8String();
#else
    if(auto java_env=java::lang::JNI::Env()){
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
#endif
}*/
