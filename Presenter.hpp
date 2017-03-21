//
//  Presenter.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef ViperPresenter_h
#define ViperPresenter_h

#include <memory>
#include <string>

#include "Disposable.hpp"
#include "Selfish.hpp"
#include "Language.hpp"
#include "Wireframe.hpp"
#include "View.hpp"

#define PRESENTER_DECL(module) struct Presenter:public Viper::Presenter<module::UserInterface, module::EventHandler, module::Input, module::Output, module::Wireframe, module::Wireframe::argument_type>,Selfish<Presenter>

namespace Viper{
    
//    template<class UI, class EH>
//    template<class V>
    struct PresenterBase : /*public EH,*/ public Disposable {
//        std::shared_ptr<UI> userInterface;
        WireframeBase wireframe;
//        V view;
        
        /*template<class T>
        void setUserInterface(std::shared_ptr<T> ptr) {
            this->userInterface = std::dynamic_pointer_cast<UI>(ptr);
        }*/
        
        virtual void dispose() override {
            this->Disposable::dispose();
//            this->userInterface = nullptr;
//            this->input = nullptr;
        }
        
        virtual ViewBase* getViewBase()=0;
    };
    
    template<class V>
    struct Presenter : public PresenterBase {
        typedef V view_type;
        V view;
        
        virtual void init(){
            /*if(W::staticArgument()){
                this->init(std::move(*W::staticArgument()));
                W::staticArgument() = {};
            }*/
        }
        
        virtual ViewBase* getViewBase() override {
            return &view;
        }
    };
}

#endif /* ViperPresenter_h */
