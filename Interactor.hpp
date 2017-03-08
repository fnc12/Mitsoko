//
//  Interactor.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef Interactor_h
#define Interactor_h

#include <memory>
#include "Disposable.hpp"
#include "Dispatch.hpp"
#include "Selfish.hpp"

#define INTERACTOR_DECL(module) struct Interactor:public Viper::Interactor<module::Output, module::Input>,Selfish<Interactor>

namespace Viper{
    
    /*template<class O,class I>
    struct Interactor:public I,public Disposable{
        std::shared_ptr<O> output;
     
        virtual void initWithArguments(const std::string &arguments){}
        
        template<class T>
        void setOutput(std::shared_ptr<T> ptr){
            this->output=std::dynamic_pointer_cast<O>(ptr);
        }
        
        virtual void dispose() override{
            this->Disposable::dispose();
            this->output=nullptr;
        }
    };*/
}

#endif /* Interactor_h */
