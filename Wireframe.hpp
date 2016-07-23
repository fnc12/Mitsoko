
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

#include <string>
#include <memory>
#include <experimental/optional>
#include <functional>
#include "Util.hpp"
#include "Selfish.hpp"

#define WIREFRAME_DECL(module,arg,ret) struct Wireframe:public Viper::Argumentable<arg,Wireframe>,Viper::Callbackable<ret,Wireframe>,Viper::WireframeBase,Selfish<Wireframe>

namespace Viper{
    
    /**
     *  This is how wireframe works:
     *  every wireframe has two main base classes:
     *  1)  Argumentable<A,W> is used to provide arguments to module.
     *      in `WIREFRAME_DECL` macro second argument must be a type module receives
     *      as an argument. Once argument specified one can override `virtual void
     *      init(A)` function in module's presenter. `init` function in presenter acts as a costructor.
     *      Second template argument must be Wireframe itself. It is used to make `Argumentable` superclass
     *      unique. Every module Argumentable superclass must be unique cause every `Argumentable<A,W>` has
     *      a `staticArgument` static optional variable. You have to assign it before creating a new module
     *      if you want to pass arguments to module. Example: `MyProfile::Wireframe::statusArgument()=5;`.
     *      If there is no need to pass an argument just pass void in WIREFRAME_DECL second argument or
     *      Argumentable<A,W> first template argument. You can still override `init()` function in presenter 
     *      when your module has void argument.
     *  2)  Callbackable<C,W> is used to specify a callback mechanism for the module. It has `std::function<void(C)> staticCallback`
     *      static variable that must be assigned before module creating. This variable is `move`d into `callback` non-static member
     *      in `Callbackable` constructor and can be accessed at any time from presenter (`wireframe.callback(5);`)
     *      or from wireframe itself. Second template argument `W` is very important cause every Callbackable superclass
     *      must be unique for every module cause it has statis variables. The third argument in `WIREFRAME_DECL` macro
     *      must be a return type or void if there nothing to return. However you cann still fire a callback if module
     *      has `void` return type - callback just does not have argument (see `Callbackable<void,W>` specialization).
     */
    
    template<class C,class W>
    struct Callbackable{
        typedef C return_type;
        std::function<void(C)> callback;
        STATIC_VAR(std::function<void(C)>, staticCallback, {});
        
        Callbackable():callback(std::move(staticCallback())){}
    };
    
    template<class W>
    struct Callbackable<void,W>{
        typedef void return_type;
        std::function<void()> callback;
        STATIC_VAR(std::function<void()>, staticCallback, {});
        
        Callbackable():callback(std::move(staticCallback())){}
    };
    
    template<class A,class W>
    struct Argumentable{
        typedef A argument_type;
        
        /**
         *  Tempopary storage for argument. Must be assigned from called module wireframe before 
         *  switching to another module.
         */
//<<<<<<< HEAD
//=======
//        STATIC_VAR(std::experimental::optional<argument_type>, staticArgument, {});
        
//>>>>>>> 0b21d31a0f0243201cd3a19d736a20d0512e468a
        static std::experimental::optional<argument_type>& staticArgument(){
            static std::experimental::optional<argument_type> res;
            return res;
        }
//<<<<<<< HEAD
//        STATIC_VAR(std::experimental::optional<argument_type>, staticArgument, {});
//=======
//>>>>>>> 0b21d31a0f0243201cd3a19d736a20d0512e468a
    };
    
    template<class W>
    struct Argumentable<void,W>{
        typedef void argument_type;
    };
    
    struct WireframeBase{
        const void *handle=nullptr;
        
//        WireframeBase(decltype(handle)handle_):handle(handle_){};
    };
}
