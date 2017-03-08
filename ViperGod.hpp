//
//  ViperGod.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef ViperGod_h
#define ViperGod_h

#include <string>
#include <tuple>
#include <type_traits>
#include <memory>
#include <map>
#include <cstring>
#include <vector>
#include "R/Modules.hpp"
#include "Module.hpp"
#include "Disposable.hpp"
#include "View.hpp"
#include "Dispatch.hpp"

namespace Viper{
    
    template<class Arg,class W,class P>
    struct PresenterIniter{
        void init(std::shared_ptr<P> presenterPointer) const{
            if(W::staticArgument()){
                presenterPointer->init(std::move(*W::staticArgument()));
                W::staticArgument() = {};
            }
        }
    };
    
    template<class W,class P>
    struct PresenterIniter<void,W,P>{
        void init(std::shared_ptr<P> presenterPointer) const{
            presenterPointer->init();
        }
    };
    
    struct God {
        typedef long ViewId;
        
        static God shared;
        
        void viewWillAppear(ViewId viewId);
        
        void viewDidAppear(ViewId viewId);
        
        void viewWillDisappear(ViewId viewId);
        
        const void* destroyView(ViewId viewId);
        
        void sendMessageToView(ViewId viewId,int messageCode,std::string argumentsString="");
        
#ifdef __ANDROID__
        void onActivityResult(ViewId viewId,int requestCode,int resultCode,jobject data);
#endif
        
        ViewId createView(const std::string &viewName,const void *handle);
    protected:
//        std::map<ViewId, ViewBase*> viewPool;
        std::map<ViewId, std::shared_ptr<PresenterBase>> presenters;
        std::map<ViewId, std::vector<std::shared_ptr<Disposable>>> disposables;
        ViewId nextViewId=0;
        
        template<typename H,typename... Tail>
        struct TupleCutter;
        
        template<typename H,typename... Tail>
        struct TupleCutter<std::tuple<H,Tail...>>{
            typedef H Head_t;
            typedef std::tuple<Tail...> Tail_t;
        };
        
        template<class T>
        std::shared_ptr<PresenterBase> _createView(const std::string &viewName,
                                              const void *handle,
                                              std::vector<std::shared_ptr<Disposable>> &disposablesVector)
        {
            typedef typename TupleCutter<T>::Head_t PageType;
//            typedef typename PageType::wireframe_type Wireframe_t;
            typedef typename PageType::presenter_type Presenter_t;
            if(Presenter_t::viewName == viewName){
            
                //  create view..
//                auto viewPointer = std::make_shared<typename PageType::view_type>(handle);
                
                //  create presenter..
                auto presenterPointer = std::make_shared<Presenter_t>();
                
                //  chain view and presenter..
//                viewPointer->setEventHandler(presenterPointer);
//                presenterPointer->setUserInterface(viewPointer);
                
                presenterPointer->wireframe.handle = handle;
                presenterPointer->view.handle = handle;
                
                //  create interactor..
//                auto interactorPointer = std::make_shared<typename PageType::interactor_type>();
                
                //  chain interactor and presenter..
//                presenterPointer->setInput(interactorPointer);
//                interactorPointer->setOutput(presenterPointer);
                
//                disposablesVector.emplace_back(std::dynamic_pointer_cast<Disposable>(viewPointer));
                disposablesVector.emplace_back(std::dynamic_pointer_cast<Disposable>(presenterPointer));
//                disposablesVector.emplace_back(std::dynamic_pointer_cast<Disposable>(interactorPointer));
                
//                interactorPointer->initWithArguments(arguments);
//                typedef typename Wireframe_t::argument_type Argument_t;
//                PresenterIniter<Argument_t, Wireframe_t, Presenter_t>().init(presenterPointer);
                presenterPointer->init();
                presenterPointer->view.init();
//                viewPointer->init();
                
//                return std::dynamic_pointer_cast<ViewBase>(viewPointer);
//                return &presenterPointer->view;
                return std::dynamic_pointer_cast<PresenterBase>(presenterPointer);
            }else{
                return this->_createView<typename TupleCutter<T>::Tail_t>(viewName,handle,disposablesVector);
            }
        }
    };
    
    template<>
    std::shared_ptr<PresenterBase> God::_createView<std::tuple<>>(const std::string &viewName,
                                                             const void *handle,
                                                             std::vector<std::shared_ptr<Disposable>> &disposables);
}

#endif /* ViperGod_h */
