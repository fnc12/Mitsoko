
#ifndef __VIPER__IOS_UTIL__NS__DICTIONARY__
#define __VIPER__IOS_UTIL__NS__DICTIONARY__

#include "Mitsoko/iOSutil/NS/Object.hpp"
#include "Mitsoko/Util.hpp"

namespace NS {
    
    struct Dictionary : public NS::Object{
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        NS::Object objectForKey(const NS::Object &aKey);
        
        int count();
        
        struct ValueAdapter{
        protected:
            Dictionary &dictionary;
            const NS::Object key;
        public:
            ValueAdapter(decltype(dictionary)d,decltype(key)k);
            
            operator NS::Object() const;
            
            template<class T>
            T as(){
                return std::move(dictionary.objectForKey(this->key).as<T>());
            }
        };
        
        ValueAdapter operator[](const NS::Object &key);
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__NS__DICTIONARY__
