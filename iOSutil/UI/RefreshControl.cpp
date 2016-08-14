//
//  RefreshControl.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "RefreshControl.hpp"

#ifdef __APPLE__

const std::string UI::RefreshControl::className="UIRefreshControl";

void UI::RefreshControl::endRefreshing(){
    this->sendMessage<void>(this->handle, "endRefreshing");
}

#endif  //__APPLE__
