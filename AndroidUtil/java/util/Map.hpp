
#pragma once

#include <type_traits>

namespace java {
    namespace util{
        template<class K,class V>
        struct Map:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/util/Map");
            
            static_assert(std::is_base_of<java::lang::Object,K>::value,"K must derive java::lang::Object");
            static_assert(std::is_base_of<java::lang::Object,V>::value,"V must derive java::lang::Object");
            
            void clear(){
                this->sendMessage<void>("clear");
            }
            
            bool containsKey(const java::lang::Object &key){
                return this->sendMessage<bool>("containsKey",key);
            }
            
            bool containsValue(const java::lang::Object &value){
                return this->sendMessage<bool>("containsValue",value);
            }
            
            bool equals(const java::lang::Object &object){
                return this->sendMessage<bool>("equals",object);
            }
            
            V get(const java::lang::Object &key){
                return (V)this->sendMessage<java::lang::Object>("get",key);
            }
            
            int hashCode(){
                return this->sendMessage<int>("hashCode");
            }
            
            bool isEmpty(){
                return this->sendMessage<bool>("isEmpty");
            }
            
            V put(const K &key,const V &value){
                return (V)this->sendMessage<java::lang::Object>("put",(java::lang::Object)key,(java::lang::Object)value);
            }
            
            V remove(const java::lang::Object &key){
                return (V)this->sendMessage<java::lang::Object>("remove",key);
            }
            
            int size(){
                return this->sendMessage<int>("size");
            }
            
#endif
        };
    }
}
