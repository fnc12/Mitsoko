
#ifndef __VIPER__ANDROID_UTIL__ANDROI__WIDGET__ABS_LIST_VIEW__
#define __VIPER__ANDROID_UTIL__ANDROI__WIDGET__ABS_LIST_VIEW__

#include "AdapterView.hpp"

namespace android{
    
    namespace widget{
        
        struct AbsListView : public AdapterView {
            
            using AdapterView::AdapterView;
            
#ifdef __ANDROID__
            
            static const std::string signature;
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROI__WIDGET__ABS_LIST_VIEW__
