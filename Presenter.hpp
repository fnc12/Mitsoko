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
//#include "Selfish.hpp"
#include "Language.hpp"
#include "Wireframe.hpp"
#include "View.hpp"

//#define PRESENTER_DECL(module) struct Presenter:public Viper::Presenter<module::UserInterface, module::EventHandler, module::Input, module::Output, module::Wireframe, module::Wireframe::argument_type>,Selfish<Presenter>

namespace Mitsoko{
    
    struct PresenterBase : public Disposable {
        WireframeBase wireframe;
        
        virtual void dispose() override {
            this->Disposable::dispose();
        }
        
        virtual ViewBase* getViewBase()=0;
    };
    
    template<class V>
    struct Presenter : public PresenterBase {
        typedef V view_type;
        V view;
        
        virtual void init(){
            //..
        }
        
        virtual ViewBase* getViewBase() override {
            return &view;
        }
    };
}

#endif /* ViperPresenter_h */
