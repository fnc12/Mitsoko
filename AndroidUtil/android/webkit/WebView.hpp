//
//  WebView.hpp
//  MyBusiness
//
//  Created by John Zakharov on 10.05.17.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#ifndef __android__webkit__WebView_hpp
#define __android__webkit__WebView_hpp

#include "Mitsoko/AndroidUtil/android/widget/AbsoluteLayout.hpp"
#include "Mitsoko/AndroidUtil/java/lang/String.hpp"

namespace android {
    
    namespace webkit {
        
        struct WebView : public android::widget::AbsoluteLayout {
            
            using AbsoluteLayout::AbsoluteLayout;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
            void loadUrl(const java::lang::String &url);
            
#endif  //  __ANDROID__
            
        };
    }
}

#endif /* __android__webkit__WebView_hpp */
