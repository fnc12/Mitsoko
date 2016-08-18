//
//  EditText.cpp
//  Groozim
//
//  Created by John Zakharov on 18.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "EditText.hpp"

#ifdef __ANDROID__

//const std::string android::widget::EditText::signature="android/widget/EditText";

auto android::widget::EditText::create(const content::Context &context)->EditText{
    return std::move(java::lang::Object::create<EditText>(context));
}

android::text::Editable android::widget::EditText::getText(){
    return this->sendMessage<android::text::Editable>("getText");
}

#endif  //__ANDROID__
