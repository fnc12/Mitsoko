
#pragma once

#include "Viper/AndroidUtil/java/lang/Class.hpp"

namespace android{
    namespace view{
        
        struct View:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/view/View");
            
            /**
             *  Implemented in ViewGroup.hpp"
             */
            template<class T>
            void setLayoutParams(const T &params);
            
            View findViewById(int id){
                return this->sendMessage<View>("findViewById",id);
            }
            
            /**
             *  This function actually doesn't exist in SDK but it is created
             *  to simplify developers finding a subview by string identifier from xml-file.
             *  =========
             *  Also it's body contains call to 'getResourseId' static function call instead of
             *  android native context.getResources.getIdentifier("view_id","id",context.getPackageName());.
             *  This is done because calling context.getResources.getIdentifier from C++ always returns
             *  incorrect id. The reason is still unknown so I decided to transfer this logic into
             *  client side. If you know the reason why context.getResources.getIdentifier doesn't work
             *  correctly please contact me fnc12@me.com. Thanks
             */
            View findViewById(const std::string &idString,const content::Context &context){
                if(auto java_env=java::lang::JNI::Env()){
                    auto niClazz=java::lang::Class::find("kz/outlawstudio/viper/NI");
                    auto signature=java::lang::Object::generateMethodSignature<int,content::Context,java::lang::String,java::lang::String>();
                    auto methodId=java_env->GetStaticMethodID(niClazz,"getResourseId",signature.c_str());
                    auto resourseId=java::lang::String::create(idString);
                    auto folderName=java::lang::String::create("id");
                    auto resID=java_env->CallStaticIntMethod(niClazz,
                                                             methodId,
                                                             context.handle,
                                                             resourseId.handle,
                                                             folderName.handle);
                    return this->findViewById(resID);
                }else{
                    return {};
                }
            }
            
            void setVisibility(int visibility){
                this->sendMessage<void>("setVisibility",visibility);
            }
            
            void setEnabled(bool enabled){
                this->sendMessage<void>("setEnabled",enabled);
            }
            
            bool isEnabled(){
                return this->sendMessage<bool>("isEnabled");
            }
            
            int getWidth(){
                return this->sendMessage<int>("getWidth");
            }
            
            int getHeight(){
                return this->sendMessage<int>("getHeight");
            }
            
            static int VISIBLE(){
                if(java::lang::Class cls=java::lang::Class::find<View>()){
                    return cls.getStaticField<int>("VISIBLE");
                }else{
                    return -1;
                }
            }
            
            static int GONE(){
                if(java::lang::Class cls=java::lang::Class::find<View>()){
                    return cls.getStaticField<int>("GONE");
                }else{
                    return -1;
                }
            }
#endif
        };
    }
}
