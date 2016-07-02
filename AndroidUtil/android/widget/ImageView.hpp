
#pragma once

#include "Viper/AndroidUtil/android/view/View.hpp"
#include "Viper/AndroidUtil/android/graphics/Bitmap.hpp"

namespace android{
    namespace widget{
        struct ImageView:public view::View{
            using View::View;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/ImageView");
            
            /**
             *  This method doesn't exist in SDK but it is created to
             *  allow user avoid requesting image resource id (just like android::view::View::findViewById).
             */
            void setImageResource(const std::string &resName,const content::Context &context){
                if(auto java_env=java::lang::JNI::Env()){
//                    auto niClazz=java::lang::Class::find(java::lang::JNI::appNamespace()+"/NI");
                    auto niClazz=java::lang::Class::find("kz/outlawstudio/viper/NI");
                    auto signature=java::lang::Object::generateMethodSignature<int,content::Context,java::lang::String,java::lang::String>();
                    auto methodId=java_env->GetStaticMethodID(niClazz,"getResourseId",signature.c_str());
                    auto resourseId=java::lang::String::create(resName);
                    auto folderName=java::lang::String::create("drawable");
                    auto resID=java_env->CallStaticIntMethod(niClazz,methodId,
                                                             context.handle,
                                                             resourseId.handle,
                                                             folderName.handle);
                    this->setImageResource(resID);
                }
            }
            
            void setImageResource(int resId){
                this->sendMessage<void>("setImageResource",resId);
            }
            
            void setImageBitmap(const android::graphics::Bitmap &bm){
                this->sendMessage<void>("setImageBitmap",bm);
            }
#endif
        };
    }
}
