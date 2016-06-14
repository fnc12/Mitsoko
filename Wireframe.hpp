
#pragma once

//#ifdef __APPLE__
#include "iOSutil/iOSutil.hpp"
//#else
#include "AndroidUtil/AndroidUtil.hpp"
//#endif

#include <string>
#include "Util.hpp"
#include "Selfish.hpp"

#define WIREFRAME_DECL(module) struct Wireframe:public Viper::Wireframe,Selfish<Wireframe>

namespace Viper{
    
    //  base class for wireframe..
    struct Wireframe{
        //..
    };
}
