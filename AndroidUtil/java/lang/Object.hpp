
#pragma once

#include "JNI.hpp"
#include "JavaRuntime.hpp"
#include <type_traits>

namespace java{
    namespace lang{
        struct Object{
            typedef const void *Handle;
            Handle handle;
            
            Object():Object(nullptr){}
            Object(Handle handle_):handle(handle_){}
            
            operator bool()const{
                return this->handle != nullptr;
            }
            
            operator Handle()const{
                return this->handle;
            }
#ifdef __ANDROID__
        protected:
            bool isGlobal=false;
        public:
            virtual ~Object(){
                if(this->isGlobal){
                    if(auto java_env=JNI::Env()){
                        java_env->DeleteGlobalRef((jobject)this->handle);
                        this->isGlobal=false;
                        this->handle=nullptr;
                    }
                }
            }
            
            /**
             *  Java `instanceof` operator analog.
             *  Usage:  if( v.instanceof<android::widget::ListView>() ){ ...
             */
            template<class T>
            bool instanceof(){
                if(auto java_env=JNI::Env()){
                    auto targetClass=java_env->FindClass(T::signature().c_str());
                    return java_env->IsInstanceOf(this->handle,targetClass);
                }else{
                    return false;
                }
            }
            
            /**
             *  Cast operator. Implements `instanceof` call and returns null object if cast failed.
             */
            template<class T,class=typename std::enable_if<std::is_base_of<T,Object>::value>::type>
            operator T (){
                if(this->instanceof<T>){
                    return this->handle;
                }else{
                    return {};
                }
            }
            
            jclass getClass(){
                if(auto java_env=JNI::Env()){
                    return java_env->GetObjectClass(static_cast<jobject>(const_cast<void*>(this->handle)));
                }else{
                    return nullptr;
                }
            }
            
            template<class T>
            T getField(const char *fieldName){
                if(auto java_env=JNI::Env()){
                    if(auto clazz=this->getClass()){
                        if(auto field = java_env->GetFieldID(clazz, fieldName, ("L"+T::signature()+";").c_str())){
                            return java_env->GetObjectField((jobject)this->handle, field);
                        }else{
                            return nullptr;
                        }
                    }else{
                        return nullptr;
                    }
                }else{
                    return nullptr;
                }
            }
            
            template<class T>
            T getField(const std::string &fieldName){
                return std::move(this->getField<T>(fieldName.c_str()));
            }
            
            void makeGlobal(){
                if(!this->isGlobal){
                    if(auto java_env=JNI::Env()){
                        this->handle=decltype(this->handle)(java_env->NewGlobalRef((jobject(this->handle))));
                        this->isGlobal=true;
                    }
                }
            }
            
            template<class RT,class ...Args>
            RT sendMessage(const std::string &message,const Args& ...args){
                return sendMessage<RT>(this->handle,message,args...);
            }
            
            template<class RT,class R,class ...Args>
            static RT sendMessage(const R &receiver,const std::string &message,const Args& ...args){
                if(auto java_env=JNI::Env()){
                    if(auto cls=java_env->GetObjectClass(jobject(receiver))){
                        auto methodSignature=std::move(generateMethodSignature<RT,Args...>());
                        if(auto methodId=java_env->GetMethodID(cls,message.c_str(),methodSignature.c_str())){
                            return MessageSender<RT>()(java_env,jobject(receiver),methodId,args...);
                        }else{
                            return MessageSender<RT>().failure();
                        }
                    }else{
                        return MessageSender<RT>().failure();
                    }
                }else{
                    return MessageSender<RT>().failure();
                }
            }
            
            template<class RT,class ...Args>
            static std::string generateMethodSignature(){
                std::stringstream ss;
                ss<<"("<<SignatureGenerator<Args...>()()<<")"<<TypeSignatureGenerator<RT>()();
                return std::move(ss.str());
            }
#endif
        };
#ifdef __ANDROID__
        template<>
        int Object::getField<int>(const char *fieldName){
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
        bool Object::getField<bool>(const char *fieldName){
            if(auto java_env=JNI::Env()){
                if(auto clazz=this->getClass()){
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
#endif
    }
}
