
#pragma once

#include "ViewManager.hpp"
#include "ViewGroup.hpp"

namespace android{
    namespace view{
        struct WindowManager:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "android/view/WindowManager");
            
            struct LayoutParams:public ViewGroup::LayoutParams{
                typedef ViewGroup::LayoutParams Super;
                using Super::Super;
                STATIC_VAR(const std::string, signature, "android/view/WindowManager$LayoutParams");
                
                static int SOFT_INPUT_STATE_VISIBLE(){
                    if(java::lang::Class cls=java::lang::Class::find<WindowManager::LayoutParams>()){
                        return cls.getStaticField<int>("SOFT_INPUT_STATE_VISIBLE");
                    }else{
                        return -1;
                    }
                }
            };
#endif
        };
    }
}
