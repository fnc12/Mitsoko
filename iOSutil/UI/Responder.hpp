
#ifndef __VIPER__IOS_UTIL__UI__RESPONDER__
#define __VIPER__IOS_UTIL__UI__RESPONDER__

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
    struct Responder:public NS::Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        bool resignFirstResponder();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__RESPONDER__
