
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/Util.hpp"

namespace NS {
    struct Dictionary:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSDictionary");
        
        NS::Object objectForKey(const NS::Object &aKey){
            return this->sendMessage<Handle>("objectForKey:", aKey.handle);
        }
        
        int count(){
            return int(this->sendMessage<NSUInteger>("count"));
        }
        
        struct ValueAdapter{
        protected:
            Dictionary &dictionary;
            const NS::Object key;
        public:
            ValueAdapter(decltype(dictionary)d,decltype(key)k):dictionary(d),key(k){}
            
            operator NS::Object()const{
                return dictionary.objectForKey(this->key);
            }
            
            template<class T>
            T as(){
                return std::move(dictionary.objectForKey(this->key).as<T>());
            }
        };
        
        ValueAdapter operator[](const NS::Object &key){
            return ValueAdapter{*this,key};
        }
#endif
    };
}
