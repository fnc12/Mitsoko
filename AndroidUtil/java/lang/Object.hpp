
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
            
            template<class T>
            void _setField(JNIEnv *java_env,jfieldID fieldId,const T &value){
                java_env->SetObjectField((jobject)this->handle, fieldId, ArgumentProxy<T>::cast(value));
            }
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
            void setField(const char *fieldName,const T &value){
                if(auto java_env=JNI::Env()){
                    if(auto clazz=this->getClass()){
                        auto signature=TypeSignatureGenerator<T>()();
                        if(auto field = java_env->GetFieldID(clazz, fieldName, signature.c_str())){
                            this->_setField(java_env, field, value);
                        }else{
                            LOGI("field is null");
                        }
                    }else{
                        LOGI("clazz is null");
                    }
                }else{
                    LOGI("java_env is null");
                }
            }
            
            template<class T>
            void setField(const std::string &fieldName,const T &value){
                this->setField(fieldName.c_str(),value);
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
            
            template<class ...Args>
            static Object create(const std::string &className,Args ...args){
                if(auto java_env=JNI::Env()){
                    if(auto cls=java_env->FindClass(className.c_str())){
                        auto methodSignature=std::move(generateMethodSignature<void,Args...>());
                        if(auto methodId=java_env->GetMethodID(cls,"<init>",methodSignature.c_str())){
                            return java_env->NewObject(cls,methodId,ArgumentProxy<Args>::cast(args)...);
                        }else{
                            return {};
                        }
                    }else{
                        return {};
                    }
                }else{
                    return {};
                }
            }
            
            template<class T,class ...Args>
            static T create(Args ...args){
                static_assert(std::is_base_of<Object,T>::value,"T must inherit java::lang::Object");
                if(auto java_env=JNI::Env()){
                    if(auto cls=java_env->FindClass(T::signature().c_str())){
                        auto methodSignature=std::move(generateMethodSignature<void,Args...>());
                        if(auto methodId=java_env->GetMethodID(cls,"<init>",methodSignature.c_str())){
                            return java_env->NewObject(cls,methodId,ArgumentProxy<Args>::cast(args)...);
                        }else{
                            return {};
                        }
                    }else{
                        return {};
                    }
                }else{
                    return {};
                }
            }
#endif
        };
#ifdef __ANDROID__
        
        template<>
        void Object::_setField<int>(JNIEnv *java_env,jfieldID fieldId,const int &value){
            LOGI("java_env->SetIntField((jobject)this->handle, fieldId, ArgumentProxy<int>::cast(value));");
            java_env->SetIntField((jobject)this->handle, fieldId, ArgumentProxy<int>::cast(value));
        }
        
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
