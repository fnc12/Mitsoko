
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__LIST_VIEW__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__LIST_VIEW__

#include "AbsListView.hpp"
#include "Viper/TableListAdapter.hpp"

namespace android{
    
    namespace widget{
        
        struct ListView:public AbsListView{
            
            using AbsListView::AbsListView;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/ListView");
            
            ListAdapter getAdapter();
            
            void setAdapter(const ListAdapter &adapter);
            
            /**
             *  This function doesn't exist in SDK. This is a special function used for
             *  settings a core crossplarform adapter to a listView.
             */
            template<class T>
            Viper::TableListAdapter::AdapterId setAdapter(T ad,
                                                          const content::Context &context)
            {
                auto pointer=std::make_shared<T>(std::move(ad));
                return this->setAdapter(pointer,context);
            }
            
            template<class T>
            Viper::TableListAdapter::AdapterId setAdapter(std::shared_ptr<T> pointer,
                                                          const content::Context &context)
            {
                auto adapterPointer=std::dynamic_pointer_cast<Viper::AdapterBase>(pointer);
                if(auto java_env=java::lang::JNI::Env()){
                    if(auto clazz=java::lang::Class::find("kz/outlawstudio/viper/ViperTableViewAdapter")){
                        auto signature=java::lang::Object::generateMethodSignature<void,ListView,content::Context>();
                        if(auto ctor = java_env->GetMethodID(clazz, "<init>", signature.c_str())){
                            ListAdapter adapter=java_env->NewObject(clazz, ctor, this->handle,context.handle);
                            auto adapterId=adapter.getField<int>("adapterId");
                            auto res=Viper::TableListAdapter::registerAdapter((const void*)(intptr_t)adapterId, adapterPointer, java_env);
                            this->setAdapter(adapter);
                            return res;
                        }else{
                            return 0;
                        }
                    }else{
                        return 0;
                    }
                }else{
                    return 0;
                }
            }
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__LIST_VIEW__
