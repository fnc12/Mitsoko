//
//  Class.cpp
//  Jako
//
//  Created by John Zakharov on 05.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Class.hpp"

#ifdef __ANDROID__

//const std::string java::lang::Class::signature="java/lang/Class";

jclass java::lang::Class::find(const std::string &signature){
    if(auto env=JNI::Env()){
        return env->FindClass(signature.c_str());
    }else{
        std::cout<<"env is null"<<std::endl;
        return nullptr;
    }
}

template<>
int java::lang::Class::_getStaticField<int>(jfieldID fieldID,JNIEnv *env){
    return env->GetStaticIntField(jclass(this->handle),fieldID);
}

#endif
