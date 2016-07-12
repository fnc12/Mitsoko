
#pragma once

#include "Button.hpp"
#include <functional>
#include <map>

namespace android{
    namespace widget{
        struct CompoundButton:public Button{
            using Button::Button;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/CompoundButton");
            
            typedef std::function<void(CompoundButton,bool)> OnCheckedChangeCallback;
            typedef std::map<int,OnCheckedChangeCallback> OnCheckedMap;
            STATIC_VAR(OnCheckedMap, onCheckedMap, {});
            
            struct OnCheckedChangeListener:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/widget/CompoundButton$OnCheckedChangeListener");
            };
            
            static void onCheckedChanged(int id,jobject sender,bool checked){
                auto it=onCheckedMap().find(id);
                if(it != onCheckedMap().end()){
                    it->second(sender,checked);
                }
            }
            
            void setChecked(bool newValue){
                this->sendMessage<void>("setChecked",newValue);
            }
            
            bool isChecked(){
                return this->sendMessage<bool>("isChecked");
            }
            
            /**
             *  TODO: add removal of callback on disposable dispose..
             */
            void setOnCheckedChangeListener(OnCheckedChangeCallback cb){
                CompoundButton::OnCheckedChangeListener l;
                cout<<"OnCheckedChangeListener l;"<<endl;
                if(cb){
                    cout<<"if(cb){"<<endl;
                    auto classSignature="kz/outlawstudio/viper/EventHandlers$CompoundButtonOnCheckedChangeListener";
                    cout<<"auto classSignature"<<endl;
                    auto callbackObject=java::lang::Object::create(classSignature);
                    java::lang::JNI::Env()->ExceptionCheck();
                    cout<<"auto callbackObject=java::lang::Object::create(classSignature);"<<endl;
                    auto callbackId=callbackObject.getField<int>("mId");
                    java::lang::JNI::Env()->ExceptionCheck();
//                    cout<<"auto callbackId"<<endl;
                    cout<<"callbackId = "<<callbackId<<endl;
                    onCheckedMap().insert({callbackId,cb});
                    cout<<"onCheckedMap().insert({callbackId,cb});"<<endl;
                    java::lang::JNI::Env()->ExceptionCheck();
                    l=(OnCheckedChangeListener)callbackObject;
//                    cout<<"l=(OnCheckedChangeListener)callbackObject;"<<endl;
                    cout<<"l = "<<l.handle<<endl;
                    java::lang::JNI::Env()->ExceptionCheck();
                }
                this->sendMessage<void>("setOnCheckedChangeListener",l);
                /*if(auto java_env=java::lang::JNI::Env()){
                    auto niClazz=java::lang::Class::find("kz/outlawstudio/viper/NI");
                    auto signature=java::lang::Object::generateMethodSignature<void,CompoundButton,CompoundButton::OnCheckedChangeListener>();
                    auto methodId=java_env->GetStaticMethodID(niClazz,"setOnCheckedChangeListenerToCompoundButton",signature.c_str());
                    java::lang::JNI::Env()->ExceptionCheck();
                    java_env->CallStaticVoidMethod(niClazz,methodId,
                                                   this->handle,
                                                   l.handle);
                }*/
                java::lang::JNI::Env()->ExceptionCheck();
            }
            
        protected:
            
            
#endif
        };
    }
}
