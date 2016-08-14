//
//  Application.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Application.hpp"

#ifdef __APPLE__

const std::string UI::Application::className="UIApplication";

UI::Application UI::Application::sharedApplication(){
    auto cls=NS::getClass(className);
    return NS::Object::sendMessage<Handle>(cls,"sharedApplication");
}

bool UI::Application::networkActivityIndicatorVisible(){
    return this->sendMessage<bool>("networkActivityIndicatorVisible");
}

void UI::Application::setNetworkActivityIndicatorVisible(bool newValue){
    this->sendMessage<void>("setNetworkActivityIndicatorVisible:", newValue);
}

#endif  //__APPLE__
