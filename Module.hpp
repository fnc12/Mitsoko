
#pragma once

namespace Viper{
    template<class V, class P /*,class W,class I*/>
    struct Module{
        typedef V view_type;
        typedef P presenter_type;
//        typedef W wireframe_type;
//        typedef I interactor_type;
    };
}
