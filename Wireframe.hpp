
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

#include <string>
#include <memory>
#include <experimental/optional>
#include <functional>
#include "Util.hpp"
#include "Selfish.hpp"

#define WIREFRAME_DECL(module,arg,ret) struct Wireframe:public Viper::Wireframe<arg,ret>,Selfish<Wireframe>

namespace Viper{
    
    template<class C>
    struct WireframeBase{
        typedef C return_type;
        std::function<void(C)> callback;
        STATIC_VAR(std::function<void(C)>, staticCallback, {});
        
        WireframeBase():callback(std::move(staticCallback())){}
    };
    
    template<>
    struct WireframeBase<void>{
        typedef void return_type;
        std::function<void()> callback;
        STATIC_VAR(std::function<void()>, staticCallback, {});
        
        WireframeBase():callback(std::move(staticCallback())){}
    };
    
    /**  
     *  Base class for wireframe.
     *  **A** is argument type.
     *  **C** is a callback (return) type.
     */
    template<class A,class C>
    struct Wireframe:WireframeBase<C>{
        typedef A argument_type;
        
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
    struct Wireframe<void,C>:WireframeBase<C>{
        typedef void argument_type;
        typedef C return_type;
        
//        Wireframe()=default;
        
    };
}
