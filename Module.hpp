
#ifndef __VIPER_MODULE_H
#define __VIPER_MODULE_H

namespace Mitsoko{
    template<class V, class P>
    struct Module{
        typedef V view_type;
        typedef P presenter_type;
    };
}

#endif /* __VIPER_MODULE_H */
