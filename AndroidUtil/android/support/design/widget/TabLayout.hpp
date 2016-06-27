
#pragma once

#include "Viper/AndroidUtil/android/widget/HorizontalScrollView.hpp"
#include "Viper/AndroidUtil/java/lang/CharSequence.hpp"

namespace android {
    namespace support{
        namespace design{
            namespace widget{
                struct TabLayout:public android::widget::HorizontalScrollView{
                    using HorizontalScrollView::HorizontalScrollView;
#ifdef __ANDROID__
                    STATIC_VAR(const std::string, signature, "android/support/design/widget/TabLayout");
                    
                    struct Tab:public java::lang::Object{
                        using Object::Object;
                        STATIC_VAR(const std::string, signature, "android/support/design/widget/TabLayout$Tab");
                        
                        Tab& setText(const std::string &text){
                            auto s=java::lang::String::create(text);
                            return this->setText(s);
                        }
                        
                        Tab& setText(const java::lang::CharSequence &text){
                            this->sendMessage<Tab>("setText",text);
                            return *this;
                        }
                    };
                    
                    static int GRAVITY_FILL(){
                        if(java::lang::Class cls=java::lang::Class::find<TabLayout>()){
                            return cls.getStaticField<int>("GRAVITY_FILL");
                        }else{
                            return -1;
                        }
                    }
                    
                    void setTabGravity(int gravity){
                        this->sendMessage<void>("setTabGravity",gravity);
                    }
                    
                    Tab newTab(){
                        return this->sendMessage<Tab>("newTab");
                    }
                    
                    void addTab(const Tab &tab){
                        this->sendMessage<void>("addTab",tab);
                    }
                    
                    Tab getTabAt(int index){
                        return this->sendMessage<Tab>("getTabAt",index);
                    }
#endif
                };
            }
        }
    }
}
