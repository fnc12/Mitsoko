
#ifndef __VIPER__IOS_UTIL__NS__MUTABLE_DICTIONARY__
#define __VIPER__IOS_UTIL__NS__MUTABLE_DICTIONARY__

#include "Dictionary.hpp"

namespace NS {
    struct MutableDictionary:public NS::Dictionary{
        using Dictionary::Dictionary;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "NSMutableDictionary");
        
        static NS::MutableDictionary create();
        
        void setObject(const NS::Object &anObject,const NS::Object &aKey);
        
        void removeObjectForKey(const NS::Object &aKey);
        
        struct ValueAdapter{
        protected:
            MutableDictionary &dictionary;
            const NS::Object key;
        public:
            ValueAdapter(decltype(dictionary)d,decltype(key)k);
            
            operator NS::Object() const;
            
            template<class T>
            T as(){
                return std::move(dictionary.objectForKey(this->key).as<T>());
            }
            
            void operator=(NS::Object value);
        };
        
        ValueAdapter operator[](const NS::Object &key);
#endif
        
    };
}

#endif  //__VIPER__IOS_UTIL__NS__MUTABLE_DICTIONARY__
