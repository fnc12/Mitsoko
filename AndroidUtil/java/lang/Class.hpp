
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__CLASS__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__CLASS__

#include "Object.hpp"

namespace java{
    
    namespace lang{
        
        struct Class : public Object {
            
            using Object::Object;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/lang/Class");
            
            static jclass find(const std::string &signature);
            
            template<class T>
            static jclass find(){
                return find(T::signature);
            }
            
            template<class T>
            T getStaticField(const char *name){
                if(auto env = java::lang::JNI::Env()){
                    if(auto fieldId = env->GetStaticFieldID(jclass(this->handle),
                                                            name,
                                                            TypeSignatureGenerator<T>()().c_str())) {
                        return this->_getStaticField<T>(fieldId, env);
                    }else{
                        return MessageSender<T>().failure();
                    }
                }else{
                    return MessageSender<T>().failure();
                }
            }
            
            template<class T>
            T getStaticField(const std::string &name){
                return std::move(getStaticField<T>(name.c_str()));
            }
            
            template<class R, class ...Args>
            R callStaticFunc(const std::string &functionName, Args ...args) {
                if(auto env = java::lang::JNI::Env()){
                    auto methodSignature = generateMethodSignature<R, Args...>();
                    auto mid = env->GetStaticMethodID(jclass(this->handle),
                                                      functionName.c_str(),
                                                      methodSignature.c_str());
                    return _callStaticFunc<R>(env, jclass(this->handle), mid, args...);
                }else{
                    return MessageSender<R>().failure();
                }
            }
            
        protected:
            
            template<class T>
            T _getStaticField(jfieldID fieldID, JNIEnv *env){
                return env->GetStaticObjectField(jclass(this->handle),fieldID);
            }
            
            template<class R, class ...Args>
            R _callStaticFunc(JNIEnv *env, jclass cls, jmethodID mid, Args ...args) {
                return env->CallStaticObjectMethod(cls,
                                                   mid,
                                                   ArgumentProxy<Args>::cast(args)...);
            }
            
#endif  //__ANDROID__
        };
        
#ifdef __ANDROID__
        template<>
        int Class::_getStaticField<int>(jfieldID fieldID, JNIEnv *env);
#endif  //__ANDROID__
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__CLASS__
