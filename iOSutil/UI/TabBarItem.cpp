//
//  TabBarItem.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TabBarItem.hpp"

#ifdef __APPLE__

const std::string UI::TabBarItem::className="UITabBarItem";

void UI::TabBarItem::setSelectedImage(const UI::Image &newValue){
    this->sendMessage<void>("setSelectedImage:", newValue.handle);
}

UI::Image UI::TabBarItem::selectedImage(){
    return this->sendMessage<Handle>("selectedImage");
}

#endif  //__APPLE__
