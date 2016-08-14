//
//  NotificationCenter.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "NotificationCenter.hpp"

#ifdef __APPLE__

const std::string NS::NotificationCenter::className="NSNotificationCenter";

NS::NotificationCenter NS::NotificationCenter::defaultCenter(){
    auto cls=NS::getClass(className);
    return NS::Object::sendMessage<Handle>(cls,"defaultCenter");
}

#endif  //__APPLE__
