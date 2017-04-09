//
//  DialogInterface.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "DialogInterface.hpp"

#ifdef __ANDROID__

const std::string android::content::DialogInterface::signature = "android/content/DialogInterface";

const std::string android::content::DialogInterface::OnClickListener::signature = "android/content/DialogInterface$OnClickListener";

void android::content::DialogInterface::cancel(){
    this->sendMessage<void>("cancel");
}

void android::content::DialogInterface::dismiss(){
    this->sendMessage<void>("dismiss");
}

#endif  //__ANDROID__
