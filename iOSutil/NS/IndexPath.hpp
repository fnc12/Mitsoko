
#ifndef __MITSOKO__IOS_UTIL__NS__INDEX_PATH__
#define __MITSOKO__IOS_UTIL__NS__INDEX_PATH__

#include "Mitsoko/iOSutil/NS/Object.hpp"

namespace NS {
    
    struct IndexPath : public NS::Object {
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        static NS::IndexPath createForRowInSection(int row, int section);
        
#endif  //  __APPLE__
    };
}

#endif /* __MITSOKO__IOS_UTIL__NS__INDEX_PATH__ */
