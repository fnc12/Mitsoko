//
//  PickerView.cpp
//  GoZebra
//
//  Created by John Zakharov on 19.02.17.
//  Copyright © 2017 Outlaw Studio. All rights reserved.
//

#include "PickerView.hpp"

#ifdef __APPLE__

const std::string UI::PickerView::className = "UIPickerView";

UI::PickerView::DoneCallbacks UI::PickerView::doneCallbacks;
UI::PickerView::CancelCallbacks UI::PickerView::cancelCallbacks;

void UI::PickerView::show(const std::vector<std::string> &entities,
                          int selectedIndex,
                          std::function<void(int)> doneCallback,
                          std::function<void(int)> cancelCallback)
{
    auto cls = NS::getClass("UIPickerViewDelegateEventHandler");
    NS::Object shared = NS::Object::sendMessage<Handle>(cls, "shared");
    auto entitiesArray = [NSMutableArray arrayWithCapacity:entities.size()];
    for(auto &entity : entities) {
        auto entityString = [NSString stringWithCString:entity.c_str() encoding:NSUTF8StringEncoding];
        [entitiesArray addObject:entityString];
    }
    auto view = shared.sendMessage<Handle>("showWithEntities:selectedIndex:",
                                           entitiesArray,
                                           NSInteger(selectedIndex));
    doneCallbacks.insert({view, doneCallback});
    cancelCallbacks.insert({view, cancelCallback});
}

#endif  //__APPLE__
