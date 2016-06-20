
#pragma once

#include "Object.hpp"

namespace java{
    namespace lang{
        struct Class:public Object{
            using Object::Object;
            STATIC_VAR(const std::string, signature, "java/lang/Class");
#ifdef __ANDROID__
            static jclass find(const std::string &signature){
                if(auto env=JNI::Env()){
                    return env->FindClass(signature.c_str());
                }else{
                    LOGI("env is null");
                    return nullptr;
                }
            }
            
            template<class T>
            static jclass find(){
                return find(T::signature());
            }
            
            /*template<class T>
            Class():Class(find<T>()){}*/
            
            template<class T>
            T getStaticField(const char *name){
                if(auto env=java::lang::JNI::Env()){
//                    if(auto cls=java::lang::Class::find<View>()){
                        if(auto fieldId=env->GetStaticFieldID(jclass(this->handle),
                                                              name,
                                                              TypeSignatureGenerator<T>()().c_str())){
                            return this->_getStaticField<T>(fieldId,env);
                        }else{
                            return -1;
                        }
                }else{
                    return MessageSender<T>().failure();
                }
            }
            
            template<class T>
            T getStaticField(const std::string &name){
                return std::move(getStaticField<T>(name.c_str()));
            }
            
        protected:
            
            template<class T>
            T _getStaticField(jfieldID fieldID,JNIEnv *env){
                return env->GetStaticObjectField(jclass(this->handle),fieldID);
            }
#endif
        };
        
#ifdef __ANDROID__
        template<>
        int Class::_getStaticField<int>(jfieldID fieldID,JNIEnv *env){
            return env->GetStaticIntField(jclass(this->handle),fieldID);
        }
#endif
    }
}
