//
//  ImageView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ImageView.hpp"

#ifdef __APPLE__

const std::string UI::ImageView::className="UIImageView";

void UI::ImageView::setImage(const UI::Image &newValue){
    this->sendMessage<void>("setImage:", newValue.handle);
}

UI::Image UI::ImageView::image(){
    return this->sendMessage<Handle>("image");
}

#endif  //__APPLE__
