
#ifndef __VIPER__ANDROID_UTIL__JAVA__LANG__LIST__
#define __VIPER__ANDROID_UTIL__JAVA__LANG__LIST__

#include "Collection.hpp"

namespace java{
    
    namespace util{
        
        /**
         *  Generic interface.
         */
        template<class E>
        struct List : public Collection {
            
            using Collection::Collection;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            int size() {
                return this->sendMessage<int>("size");
            }
            
            bool isEmpty() {
                return this->sendMessage<bool>("isEmpty");
            }
            
            bool contains(java::lang::Object obj) {
                return this->sendMessage<bool>("contains", obj);
            }
            
            E get(int n) {
                return (E)this->sendMessage<java::lang::Object>("get", n);
            }
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__JAVA__LANG__LIST__
