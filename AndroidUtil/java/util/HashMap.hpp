
#pragma once

#include "AbstractMap.hpp"

namespace java {
    namespace util{
        
        template<class K,class V>
        struct HashMap:public AbstractMap<K, V>{
            typedef AbstractMap<K, V> Super;
            typedef HashMap<K,V> Self;
            using Super::Super;
            typedef V value_type;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/util/HashMap");
            
            static Self create(){
                return std::move(java::lang::Object::create<Self>());
            }
            
            V put(const K &key,const V &value){
                return (V)this->template sendMessage<java::lang::Object>("put",(java::lang::Object)key,(java::lang::Object)value);
            }
            
            V get(const java::lang::Object &key){
                auto res=this->template sendMessage<java::lang::Object>("get",key);
//                cout<<"auto res=this->template sendMessage<V>(\"get\",key);"<<endl;
                java::lang::JNI::Env()->ExceptionCheck();
                return (V)res;
            }
            
            V remove(const java::lang::Object &key){
                return (V)this->template sendMessage<java::lang::Object>("remove",key);
            }
#endif
        };
    }
}
