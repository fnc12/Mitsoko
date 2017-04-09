
#ifndef __VIPER__ANDROID_UTIL__JAVA__UTIL__HASH_MAP__
#define __VIPER__ANDROID_UTIL__JAVA__UTIL__HASH_MAP__

#include "AbstractMap.hpp"

namespace java {
    
    namespace util{
        
        template<class K,class V>
        struct HashMap : public AbstractMap<K, V> {
            
            typedef AbstractMap<K, V> Super;
            typedef HashMap<K, V> Self;
            
            using Super::Super;
            
            typedef V value_type;
            
#ifdef __ANDROID__
            
            static const std::string signature;
//            STATIC_VAR(const std::string, signature, "java/util/HashMap");
            
            static Self create();
            
            V put(const K &key,const V &value);
            
            V get(const java::lang::Object &key);
            
            V remove(const java::lang::Object &key);
            
#endif  //__ANDROID__
            
        };
        
#ifdef __ANDROID__
        
        template<class K,class V>
        const std::string HashMap<K, V>::signature = "java/util/HashMap";
#endif  //__ANDROID__
    }
}

#ifdef __ANDROID__

/*template<class K,class V>
 const std::string java::util::HashMap<K,V>::signature="java/util/HashMap";*/

template<class K, class V>
auto java::util::HashMap<K,V>::create() -> Self {
    return std::move(java::lang::Object::create<Self>());
}

template<class K,class V>
V java::util::HashMap<K,V>::put(const K &key,const V &value){
    return (V)this->template sendMessage<java::lang::Object>("put",(java::lang::Object)key,(java::lang::Object)value);
}

template<class K,class V>
V java::util::HashMap<K,V>::get(const java::lang::Object &key){
    auto res=this->template sendMessage<java::lang::Object>("get",key);
    //                cout<<"auto res=this->template sendMessage<V>(\"get\",key);"<<endl;
//    java::lang::JNI::Env()->ExceptionCheck();
    return (V)res;
}

template<class K,class V>
V java::util::HashMap<K,V>::remove(const java::lang::Object &key){
    return (V)this->template sendMessage<java::lang::Object>("remove",key);
}

#endif  //__ANDROID__

#endif  //__VIPER__ANDROID_UTIL__JAVA__UTIL__HASH_MAP__
