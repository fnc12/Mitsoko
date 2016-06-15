
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

#include <string>
#include <memory>
#include <experimental/optional>
#include "Util.hpp"
#include "Selfish.hpp"

#define WIREFRAME_DECL(module,arg,ret) struct Wireframe:public Viper::Wireframe<arg,ret>,Selfish<Wireframe>

namespace Viper{
    
    /**  
     *  Base class for wireframe.
     *  **A** is argument type.
     *  **C** is a callback (return) type.
     */
    template<class A,class C>
    struct Wireframe{
        typedef A argument_type;
        typedef C return_type;
        
//        Wireframe():argument(std::move(*staticArgument())){}
        
//        A argument;
        
        /**
         *  Tempopary storage for argument. Must be assigned from called module wireframe before 
         *  switching to another module.
         */
        STATIC_VAR(std::experimental::optional<argument_type>, staticArgument, {});
    };
    
    /**
     *  Specialization for void argument.
     */
    template<class C>
    struct Wireframe<void,C>{
        typedef void argument_type;
        typedef C return_type;
        
//        Wireframe()=default;
        
    };
}
