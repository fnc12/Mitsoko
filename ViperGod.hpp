//
//  ViperGod.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef ViperGod_h
#define ViperGod_h

#include "ViperGodBase.hpp"
#include "R/Modules.hpp"

namespace Viper{
    using namespace Modules;
    struct God:public Viper::ViperGodBase{
        
        static God& shared(){
            static God res;
            return res;
        }
        
        ViewId createView(const std::string &viewName,const void *handle){
            std::vector<std::shared_ptr<Disposable>> disposablesVector;
            auto viewPointer=this->_createView<R::ModulesTuple>(viewName,handle,disposablesVector);
            if(viewPointer){
                const auto viewId=this->nextViewId++;
                this->viewPool.insert({viewId,viewPointer});
                this->disposables.insert({viewId,std::move(disposablesVector)});
                return viewId;
            }else{
                return -1;
            }
        }
    protected:
        
        template<class T>
        std::shared_ptr<ViewBase> _createView(const std::string &viewName,
                                              const void *handle,
                                              std::vector<std::shared_ptr<Disposable>> &disposablesVector)
        {
            typedef typename TupleCutter<T>::Head_t PageType;
            typedef typename PageType::wireframe_type Wireframe_t;
            if(Wireframe_t::viewName()==viewName){
                
                //  create view..
                auto viewPointer=std::make_shared<typename PageType::view_type>(handle);
                const auto arguments=viewPointer->arguments();
                
                //  create presenter..
                typedef typename PageType::presenter_type Presenter_t;
                auto presenterPointer=std::make_shared<Presenter_t>();
                
                //  chain view and presenter..
                viewPointer->setEventHandler(presenterPointer);
                presenterPointer->setUserInterface(viewPointer);
                
                //  create interactor..
                auto interactorPointer=std::make_shared<typename PageType::interactor_type>();
                
                //  chain interactor and presenter..
                presenterPointer->setInput(interactorPointer);
                interactorPointer->setOutput(presenterPointer);
                
                disposablesVector.emplace_back(std::dynamic_pointer_cast<Disposable>(viewPointer));
                disposablesVector.emplace_back(std::dynamic_pointer_cast<Disposable>(presenterPointer));
                disposablesVector.emplace_back(std::dynamic_pointer_cast<Disposable>(interactorPointer));
                
                viewPointer->init();
//                interactorPointer->initWithArguments(arguments);
                /*if(!std::is_same<typename Wireframe_t::argument_type, void>::value){
                    if(Wireframe_t::staticArgument()){
                        presenterPointer->init(std::move(*Wireframe_t::staticArgument()));
                        Wireframe_t::staticArgument() = {};
                    }
                }else{
                    presenterPointer->init();
                }*/
                typedef typename Presenter_t::P PresenterBase_t;
                presenterPointer->PresenterBase_t::init();
                
                return std::dynamic_pointer_cast<ViewBase>(viewPointer);
            }else{
                return this->_createView<typename TupleCutter<T>::Tail_t>(viewName,handle,disposablesVector);
            }
        }
    };
    
    template<>
    std::shared_ptr<ViewBase> God::_createView<std::tuple<>>(const std::string &viewName,
                                                             const void *handle,
                                                             std::vector<std::shared_ptr<Disposable>> &disposables)
    {
        return {};
    }
}

#endif /* ViperGod_h */
