//
//  PageControl.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "PageControl.hpp"

#ifdef __APPLE__

const std::string UI::PageControl::className="UIPageControl";

void UI::PageControl::setNumberOfPages(int newValue){
    this->sendMessage<void>("setNumberOfPages:", NSInteger(newValue));
}

int UI::PageControl::numberOfPages(){
    return int(this->sendMessage<NSInteger>("numberOfPages"));
}

#endif  //__APPLE__
