//
//  ViewPresenterIF.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef ViewPresenterIF_h
#define ViewPresenterIF_h

#include <string>
#include <tuple>
#include <functional>
#include <memory>

#include "TableListAdapter.hpp"

namespace Viper{
    
    //  base class for 'presenter for view' interface..
    struct EventHandler{
        virtual void viewWillAppear(){}
        virtual void viewWillDisappear(){}
        virtual void viewDidAppear(){}
    };
    
    //  base class for 'view for presenter' interface..
    struct UserInterface{
        virtual void errorHappened(const std::string &errorText){}
    };
}

#endif /* ViewPresenterIF_h */
