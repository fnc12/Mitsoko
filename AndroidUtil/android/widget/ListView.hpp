
#pragma once

#include "AbsListView.hpp"
#include "Viper/TableListAdapter.hpp"

namespace android{
    namespace widget{
        struct ListView:public AbsListView{
            using AbsListView::AbsListView;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/widget/ListView");
            
            ListAdapter getAdapter(){
                return this->sendMessage<ListAdapter>("getAdapter");
            }
            
            void setAdapter(const ListAdapter &adapter){
//                cout<<"setAdapter("<<adapter.handle<<")"<<endl;
//                cout<<"this = "<<this<<endl;
                this->sendMessage<void>("setAdapter",adapter);
            }
            
            /**
             *  This function doesn't exist in SDK. This is a special function used for
             *  settings a core crossplarform adapter to a listView.
             */
            template<class T>
            Viper::TableListAdapter::AdapterId setAdapter(T ad,
                                                          const content::Context &context)
            {
                auto pointer=std::make_shared<T>(std::move(ad));
//                cout<<"pointer = "<<pointer<<endl;
                return this->setAdapter(pointer,context);
            }
            
            template<class T>
            Viper::TableListAdapter::AdapterId setAdapter(std::shared_ptr<T> pointer,
                                                          const content::Context &context)
            {
                auto adapterPointer=std::dynamic_pointer_cast<Viper::AdapterBase>(pointer);
//                cout<<"adapterPointer = "<<adapterPointer<<endl;
                if(auto java_env=java::lang::JNI::Env()){
                    if(auto clazz=java::lang::Class::find("kz/outlawstudio/viper/ViperTableViewAdapter")){
                        auto signature=java::lang::Object::generateMethodSignature<void,ListView,content::Context>();
                        if(auto ctor = java_env->GetMethodID(clazz, "<init>", signature.c_str())){
                            ListAdapter adapter=java_env->NewObject(clazz, ctor, this->handle,context.handle);
//                            cout<<"adapter = "<<adapter.handle<<endl;
//                            adapterPointer->activityHandle=context.handle;
                            auto adapterId=adapter.getField<int>("adapterId");
//                            cout<<"adapterId = "<<adapterId<<endl;
                            auto res=Viper::TableListAdapter::registerAdapter((const void*)(intptr_t)adapterId, adapterPointer, java_env);
//                            cout<<"res = "<<res<<endl;
                            this->setAdapter(adapter);
//                            cout<<"this->setAdapter(adapter);"<<endl;
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
#endif
        };
    }
}
