
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

#include <string>
#include <memory>
#include <experimental/optional>
#include <functional>
#include <iostream>

#include "Util.hpp"
#include "Selfish.hpp"

#define WIREFRAME_DECL(module,arg,ret) struct Wireframe:public Viper::Argumentable<arg,Wireframe>,Viper::Callbackable<ret,Wireframe>,Viper::WireframeBase,Selfish<Wireframe>

namespace Viper{
    
    namespace tuple_helper {
        
        template<size_t N, class ...Args>
        struct iterator {
            
            template<class L>
            void operator()(std::tuple<Args...> &t, L l) {
                l(std::get<N>(t));
                iterator<N - 1, Args...>()(t, l);
            }
        };
        
        template<class ...Args>
        struct iterator<0, Args...>{
            template<class L>
            void operator()(std::tuple<Args...> &t, L l) {
                l(std::get<0>(t));
            }
        };
        
        template<size_t N>
        struct iterator<N> {
            
            template<class L>
            void operator()(std::tuple<> &t, L l) {
                //..
            }
        };
    }
    
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
    struct Callbackable {
        typedef C return_type;
        std::function<void(C)> callback;
        STATIC_VAR(std::function<void(C)>, staticCallback, {});
        
        Callbackable():callback(std::move(staticCallback())){}
    };
    
    template<class W>
    struct Callbackable<void,W> {
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
        static std::experimental::optional<argument_type>& staticArgument(){
            static std::experimental::optional<argument_type> res;
            return res;
        }
    };
    
    template<class W>
    struct Argumentable<void, W> {
        typedef void argument_type;
    };
    
    template<class T>
    struct Argument_t {
        T t;
    };
    
    template<class T>
    struct Callback_t {
        T t;
    };
    
    struct WireframeBase {
        const void *handle = nullptr;
        
        template<class P, class T>
        void processOpenArgument(Argument_t<T> a) {
            P::staticArgument() = std::move(a.t);
//            std::cout << "void processOpenArgument(Argument_t<T> a)" << std::endl;
            //            LOGI("staticArgument assigned");
        }
        
        template<class P, class T>
        void processOpenArgument(Callback_t<T> c) {
            P::staticCallback() = std::move(c.t);
//            std::cout << "void processOpenArgument(Callback_t<T> c)" << std::endl;
        }
        
//        template<class P, class ...Args>
//        void processOpenArguments(Args ...args);
        
        /*template<class P, class ...Args>
        void processOpenArguments(Args ... args) {
            auto t = std::make_tuple(std::forward<Args>(args)...);
            tuple_helper::iterator<std::tuple_size<decltype(t)>::value, Args...>()(t, [=](auto &a){
                this->processOpenArgument<P>(a);
            });
//            this->processOpenArgument<P>(std::move(h));
//            this->processOpenArguments<P>(std::forward<Args>(args)...);
            
        }*/
        
        /*template<class P, class T, class ...Args>
        void processOpenArguments<P, Argument_t<T>, Args...>(Argument_t<T> a, Args ...args) {
            P::staticArgument() = std::move(a.t);
            this->processOpenArguments<P, Args...>(args...);
        }
        
        template<class P, class T, class ...Args>
        void processOpenArguments<P, Callback_t<T>, Args...>(Callback_t<T> c, Args ...args) {
            P::staticCallback() = std::move(c.t);
            this->processOpenArguments<P, Args...>(args...);
        }*/
        
        /*template<class P>
        void processOpenArguments<P>(){
            //..
        }*/
        
        /*template<class P, class T>
        void processOpenArgument(T t) {
            static_assert(false, "unknown argument type in processOpenArgument");
        }*/
        
        /* {
            //..
            std::cout << "void processOpenArguments(Args ...args)" << std::endl;
        }*/
        
        /*template<class P, class H, class ...Args>
        void processOpenArguments(H h, Args ...args) {
            std::cout << __func__ << std::tuple_size<std::tuple<Args...>>::value << ", H = " << typeid(H).name() << std::endl;
            this->processOpenArgument<P>(std::move(h));
            this->processOpenArguments<P>(std::forward<Args>(args)...);
        }*/
        
        template<class I, class A>
        void open(const std::string &viewName, I i, A a) {
#ifdef __APPLE__
            i(this->handle, viewName);
#else
            a(this->handle, viewName);
#endif
        }
        
        template<class P, class I, class A, class ...Args>
        void open(I i, A a, Args ...args) {
//            std::cout << "open arguments count = " << std::tuple_size<std::tuple<Args...>>::value << std::endl;
            typedef std::tuple<Args...> tuple_t;
            auto t = std::make_tuple(std::forward<Args>(args)...);
//            this->processOpenArguments<P>(std::forward<Args>(args)...);
            tuple_helper::iterator<std::tuple_size<tuple_t>::value - 1, Args...> it;
            it(t, [=](auto &v){
//                std::cout << "ototo" << std::endl;
                this->processOpenArgument<P>(std::move(v));
            });
            this->open(P::viewName, i, a);
        }
        
        template<class I, class A>
        void close(I i, A a) {
#ifdef __APPLE__
            i(this->handle);
#else
            a(this->handle);
#endif
        }
    };
    
    struct NavigationPusher {
        bool animated = true;
        
        void operator()(const void *handle, const std::string &viewName);
    };
    
    struct NavigationPoper {
        bool animated = true;
        
        void operator()(const void *handle);
    };
    
    struct NavigationClassPoper {
        std::string targetClassName;
        bool animated = true;
        
        NavigationClassPoper() = delete;
        
        NavigationClassPoper(const std::string &target, bool animated = true);
        
        void operator()(const void *handle);
    };
    
    struct FragmentStarter {
        void operator()(const void *handle, const std::string &viewName);
    };
    
    struct ActivityStarter {
        bool finishSelf = false;
        std::shared_ptr<int> result;
        
        ActivityStarter(bool finishSelf_ = false):finishSelf(finishSelf_){}
        
        ActivityStarter(bool finishSelf_, int result_):finishSelf(finishSelf_),result(std::make_shared<int>(result_)){}
        
        void operator()(const void *handle, const std::string &viewName);
    };
    
    struct ActivityCloser {
        std::shared_ptr<int> result;
        
        ActivityCloser();
        
        ActivityCloser(int result);
        
        void operator()(const void *handle);
    };
    
    template<class T>
    Argument_t<T> argument(T t) {
        return {t};
    }
    
    template<class T>
    Callback_t<T> callback(T t) {
        return {t};
    }
}
