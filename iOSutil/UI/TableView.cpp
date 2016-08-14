//
//  TableView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TableView.hpp"

#ifdef __APPLE__

const std::string UI::TableView::className="UITableView";

void UI::TableView::reloadSections(const NS::IndexSet &indexSet,RowAnimation animation){
    auto is=indexSet.handle;
    this->sendMessage<void>("reloadSections:withRowAnimation:", is,UITableViewRowAnimation(animation));
}

void UI::TableView::reloadData(){
    this->sendMessage<void>(this->handle, "reloadData");
}

void UI::TableView::beginUpdates(){
    this->sendMessage<void>(this->handle, "beginUpdates");
}

UI::ImageView UI::TableView::Cell::imageView(){
    return this->sendMessage<Handle>("imageView");
}

UI::Label UI::TableView::Cell::detailTextLabel(){
    return this->sendMessage<Handle>("detailTextLabel");
}

UI::Label UI::TableView::Cell::textLabel(){
    return this->sendMessage<Handle>("textLabel");
}

void UI::TableView::Cell::setAccessoryType(AccessoryType newValue){
    this->sendMessage<void>("setAccessoryType:", UITableViewCellAccessoryType(newValue));
}

auto UI::TableView::Cell::accessoryType()->AccessoryType{
    return AccessoryType(this->sendMessage<UITableViewCellAccessoryType>("accessoryType"));
}

#endif  //__APPLE__
