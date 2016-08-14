//
//  TabBarController.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TabBarController.hpp"

#ifdef __APPLE__

const std::string UI::TabBarController::className="UITabBarController";

void UI::TabBarController::setViewControllers(const NS::Array &newValue){
    this->sendMessage<void>("setViewControllers:", newValue.handle);
}

NS::Array UI::TabBarController::viewControllers(){
    return this->sendMessage<Handle>("viewControllers");
}

#endif  //__APPLE__
