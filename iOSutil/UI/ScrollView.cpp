//
//  ScrollView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ScrollView.hpp"

#ifdef __APPLE__

const std::string UI::ScrollView::className="UIScrollView";

void UI::ScrollView::setContentSize(const CG::Size &newValue){
    this->sendMessage<void>("setContentSize:", CGSize(newValue));
}

CG::Size UI::ScrollView::contentSize(){
    return this->sendMessage<CGSize>("contentSize");
}

#endif  //__APPLE__
