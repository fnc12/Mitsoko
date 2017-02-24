//
//  PickerView.hpp
//  GoZebra
//
//  Created by John Zakharov on 19.02.17.
//  Copyright © 2017 Outlaw Studio. All rights reserved.
//

#ifndef PickerView_hpp
#define PickerView_hpp

#include "View.hpp"

#include <vector>
#include <string>
#include <functional>
#include <map>

namespace UI {
    
    struct PickerView : public UI::View {
        
        using View::View;
        
#ifdef __APPLE__
        static const std::string className;
        
        typedef std::function<void(int)> DoneCallback;
        typedef std::function<void(int)> CancelCallback;
        
        static void show(const std::vector<std::string> &entities,
                         int selectedIndex,
                         DoneCallback doneCallback,
                         CancelCallback cancelCallback);
        
        /**
         *  These two maps must not be accessed directly. They are used
         *  to store callbacks that are fired from UIPickerViewDelegateEventHandler service class.
         */
        typedef std::map<Handle, DoneCallback> DoneCallbacks;
        static DoneCallbacks doneCallbacks;
        
        typedef std::map<Handle, CancelCallback> CancelCallbacks;
        static CancelCallbacks cancelCallbacks;
        
#endif  //__APPLE__
    };
}

#endif /* PickerView_hpp */
