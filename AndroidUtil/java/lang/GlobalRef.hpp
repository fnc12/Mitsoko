//
//  GlobalRef.h
//  solve-it-2
//
//  Created by John Zakharov on 08.10.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__GLOBAL_REF__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__GLOBAL_REF__

#include "JNI.hpp"
#include "Object.hpp"

#ifdef __ANDROID__
#include <jni.h>
#endif

namespace java{
    namespace lang{
        
        /*template<class T>
        struct GlobalRef:public T{
            
            typedef Object::Handle Handle;
            
            GlobalRef():T(){}
            
#ifdef __ANDROID__
            GlobalRef(Handle handle):T(handle){
                if(this->handle){
                    this->handle=java::lang::JNI::Env()->NewGlobalRef(jobject(this->handle));
                }
            }
            
            //  global ref is unique..
            GlobalRef(const GlobalRef &other)=delete;
            GlobalRef& operator=(const GlobalRef &other)=delete;
            
            GlobalRef(GlobalRef &&other)=default{
                this->handle=other.handle;
                other.handle=nullptr;
            }
            
            GlobalRef& operator=(GlobalRef &&other){
                this->handle=other.handle;
                other.handle=nullptr;
                return *this;
            }
            
            T get() const{
                return T(this->handle);
                //                return this;
            }
            
            void swap(GlobalRef &other){
                this->handle=other.handle;
                other.handle=nullptr;
            }
            
            ~GlobalRef(){
                if(this->handle){
                    java::lang::JNI::Env()->DeleteGlobalRef(jobject(this->handle));
                    this->handle=nullptr;
                }
            }
#endif  //__ANDROID__
        };
        
        template<class T>
        GlobalRef<T> makeGlobalRef(const T &object){
            return object.handle;
        }*/
    }
}

#endif /* __VIPER__ANDROID_UTIL__JAVA__LANG__GLOBAL_REF__ */
