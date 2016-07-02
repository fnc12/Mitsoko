
#pragma once

#include "Dictionary.hpp"

namespace NS {
    struct MutableDictionary:public NS::Dictionary{
        using Dictionary::Dictionary;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "NSMutableDictionary");
        
        static NS::MutableDictionary create(){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "new");
//            Handle res=handle;
            return handle;
        }
        
        void setObject(const NS::Object &anObject,const NS::Object &aKey){
            this->sendMessage<void>("setObject:forKey:", anObject.handle, aKey.handle);
        }
        
        void removeObjectForKey(const NS::Object &aKey){
            this->sendMessage<void>("removeObjectForKey:", aKey.handle);
        }
        
        struct ValueAdapter{
        protected:
            MutableDictionary &dictionary;
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
            
            void operator=(NS::Object value){
                dictionary.setObject(value, this->key);
            }
        };
        
        ValueAdapter operator[](const NS::Object &key){
            return ValueAdapter{*this,key};
        }
#endif
        
    };
}
