//
//  PresenterInteractorIF.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef PresenterInteractorIF_h
#define PresenterInteractorIF_h

#include <string>
#include <functional>

namespace Viper{
    
    //  base class for 'presenter for interactor' interface..
    struct Output{
        virtual void errorHappened(const std::string &errorText){};
    };
    
    //  base class for 'interactor for presenter' interface..
    struct Input{
        virtual void viewWillAppear(){}
        virtual void viewDidAppear(){}
    };
}

#endif /* PresenterInteractorIF_h */
