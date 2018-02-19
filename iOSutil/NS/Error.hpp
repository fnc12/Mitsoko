
#ifndef Error_hpp
#define Error_hpp

#include "Object.hpp"
#include "Dictionary.hpp"

namespace NS {
    
    struct Error : public NS::Object{
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        std::string domain();
        
        int code();
        
        NS::Dictionary userInfo();
        
        std::string localizedDescription();
        
#endif  //__APPLE__
        
    };
}

#endif /* Error_hpp */
