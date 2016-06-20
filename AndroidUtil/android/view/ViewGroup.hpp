
#pragma once

#include "View.hpp"
#include <type_traits>

namespace android{
    namespace view{
        struct ViewGroup:public View{
            using View::View;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/view/ViewGroup");
            
            struct LayoutParams:public java::lang::Object{
                using Object::Object;
                STATIC_VAR(const std::string, signature, "android/view/ViewGroup$LayoutParams");
                
                static int MATCH_PARENT(){
                    if(java::lang::Class cls=java::lang::Class::find<LayoutParams>()){
                        return cls.getStaticField<int>("MATCH_PARENT");
                    }else{
                        return -1;
                    }
                }
                
                static int WRAP_CONTENT(){
                    if(java::lang::Class cls=java::lang::Class::find<LayoutParams>()){
                        return cls.getStaticField<int>("WRAP_CONTENT");
                    }else{
                        return -1;
                    }
                }
            };
            
            struct MarginLayoutParams:public LayoutParams{
                using LayoutParams::LayoutParams;
                STATIC_VAR(const std::string, signature, "android/view/ViewGroup$MarginLayoutParams");
            };
#endif
        };
#ifdef __ANDROID__
        template<class T>
        void View::setLayoutParams(const T &params){
            auto baseParams=(ViewGroup::LayoutParams)params;
            this->sendMessage<void>("setLayoutParams",baseParams);
        }
        
        template<>
        void View::setLayoutParams<ViewGroup::LayoutParams>(const ViewGroup::LayoutParams &params){
//            auto baseParams=(ViewGroup::LayoutParams)params;
            this->sendMessage<void>("setLayoutParams",params);
        }
#endif
    }
}
