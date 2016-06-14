//
//  Presenter.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef Presenter_h
#define Presenter_h

#include <memory>
#include <string>
#include "Disposable.hpp"
#include "Selfish.hpp"

#define PRESENTER_DECL(module) struct Presenter:public Viper::Presenter<module::UserInterface, module::EventHandler, module::Input, module::Output, module::Wireframe>,Selfish<Presenter>

namespace Viper{
    
    template<class UI,class EH,class I,class O,class W>
    struct Presenter:public EH,public O,public Disposable{
        std::shared_ptr<UI> userInterface;
        std::shared_ptr<I> input;
        W wireframe;
        
        template<class T>
        void setUserInterface(std::shared_ptr<T> ptr){
            this->userInterface=std::dynamic_pointer_cast<UI>(ptr);
        }
        
        template<class T>
        void setInput(std::shared_ptr<T> ptr){
            this->input=std::dynamic_pointer_cast<I>(ptr);
        }
        
        virtual void dispose() override{
            this->Disposable::dispose();
            this->userInterface=nullptr;
            this->input=nullptr;
        }
    };
}

#endif /* Presenter_h */
