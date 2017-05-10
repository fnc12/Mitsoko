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

void android::webkit::WebView::loadData(const std::string &data,
                                        const std::string &mimeType,
                                        const std::string &encoding)
{
    this->sendMessage<void>("loadData", java::lang::String::create(data), java::lang::String::create(mimeType), java::lang::String::create(encoding));
}

#endif  //__ANDROID__
