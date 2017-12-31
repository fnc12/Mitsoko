//
//  Object.cpp
//  Jako
//
//  Created by John Zakharov on 05.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Object.hpp"

java::lang::Object::Object():Object(nullptr){}

java::lang::Object::Object(Handle handle_):handle(handle_){}

java::lang::Object::operator bool() const{
    return this->handle != nullptr;
}

#ifdef __ANDROID__

const std::string java::lang::Object::signature = "java/lang/Object";

java::lang::Object::~Object(){
    /*if(this->isGlobal){
        if(auto java_env=JNI::Env()){
            java_env->DeleteGlobalRef((jobject)this->handle);
            this->isGlobal=false;
            this->handle=nullptr;
        }
    }*/
}

template<>
void java::lang::Object::_setField<int>(JNIEnv *java_env, jfieldID fieldId, const int &value){
    java_env->SetIntField((jobject)this->handle, fieldId, ArgumentProxy<int>::cast(value));
}

template<>
void java::lang::Object::_setField<bool>(JNIEnv *java_env, jfieldID fieldId, const bool &value){
    java_env->SetBooleanField((jobject)this->handle, fieldId, ArgumentProxy<bool>::cast(value));
}


template<>
int java::lang::Object::getField<int>(const char *fieldName){
    if(auto java_env=JNI::Env()){
        if(auto clazz=this->getClass()){
            if(auto field = java_env->GetFieldID(clazz, fieldName, TypeSignatureGenerator<int>()().c_str())){
                return java_env->GetIntField((jobject)this->handle, field);
            }else{
                return MessageSender<int>().failure();
            }
        }else{
            return MessageSender<int>().failure();;
        }
    }else{
        return MessageSender<int>().failure();;
    }
}

template<>
bool java::lang::Object::getField<bool>(const char *fieldName){
    if(auto java_env = JNI::Env()){
        if(auto clazz = this->getClass()){
            if(auto field = java_env->GetFieldID(clazz, fieldName, TypeSignatureGenerator<bool>()().c_str())){
                return java_env->GetBooleanField((jobject)this->handle, field);
            }else{
                return MessageSender<bool>().failure();
            }
        }else{
            return MessageSender<bool>().failure();
        }
    }else{
        return MessageSender<bool>().failure();
    }
}

jclass java::lang::Object::getClass(){
    if(auto java_env = JNI::Env()){
        return java_env->GetObjectClass(static_cast<jobject>(const_cast<void*>(this->handle)));
    }else{
        return nullptr;
    }
}

/*void java::lang::Object::makeGlobal(){
    if(!this->isGlobal){
        if(auto java_env=JNI::Env()){
            this->handle=decltype(this->handle)(java_env->NewGlobalRef((jobject(this->handle))));
            this->isGlobal=true;
        }
    }
}*/

#endif  //__ANDROID__
