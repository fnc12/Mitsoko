//
//  WebView.cpp
//  MyBusiness
//
//  Created by John Zakharov on 10.05.17.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#include "WebView.hpp"

#ifdef __ANDROID__

const std::string android::webkit::WebView::signature = "android/webkit/WebView";

void android::webkit::WebView::loadUrl(const java::lang::String &url) {
    this->sendMessage<void>("loadUrl", url);
}

#endif  //__ANDROID__
