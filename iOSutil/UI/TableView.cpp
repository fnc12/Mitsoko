//
//  TableView.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "TableView.hpp"

#ifdef __APPLE__

const std::string UI::TableView::className = "UITableView";
const std::string UI::TableView::Cell::className = "UITableViewCell";

void UI::TableView::reloadSections(const NS::IndexSet &indexSet, RowAnimation animation){
    auto is = indexSet.handle;
    this->sendMessage<void>("reloadSections:withRowAnimation:", is, UITableViewRowAnimation(animation));
}

void UI::TableView::reloadData() {
    this->sendMessage<void>(this->handle, "reloadData");
}

void UI::TableView::beginUpdates() {
    this->sendMessage<void>(this->handle, "beginUpdates");
}

UI::Color UI::TableView::separatorColor() {
    return this->sendMessage<Handle>("separatorColor");
}

void UI::TableView::setSeparatorColor(const UI::Color &value) {
    this->sendMessage<void>("setSeparatorColor:", value.handle);
}

UI::View UI::TableView::tableFooterView() {
    return this->sendMessage<Handle>("tableFooterView");
}

void UI::TableView::setTableFooterView(const UI::View &value) {
    this->sendMessage<void>("setTableFooterView:", value.handle);
}

UI::ImageView UI::TableView::Cell::imageView() {
    return this->sendMessage<Handle>("imageView");
}

UI::Label UI::TableView::Cell::detailTextLabel() {
    return this->sendMessage<Handle>("detailTextLabel");
}

UI::Label UI::TableView::Cell::textLabel() {
    return this->sendMessage<Handle>("textLabel");
}

void UI::TableView::Cell::setAccessoryType(AccessoryType newValue) {
    this->sendMessage<void>("setAccessoryType:", UITableViewCellAccessoryType(newValue));
}

void UI::TableView::Cell::setSelectionStyle(SelectionStyle newValue) {
    this->sendMessage<void>("setSelectionStyle:", UITableViewCellSelectionStyle(newValue));
}

void UI::TableView::Cell::setSeparatorInset(const UI::EdgeInsets &value) {
    this->sendMessage<void>("setSeparatorInset:", UIEdgeInsets(value));
}

UI::EdgeInsets UI::TableView::Cell::separatorInset() {
    return UI::EdgeInsets(this->sendMessage<UIEdgeInsets>("separatorInset"));
}

auto UI::TableView::Cell::selectionStyle() -> SelectionStyle {
    return SelectionStyle(this->sendMessage<UITableViewCellSelectionStyle>("selectionStyle"));
}

auto UI::TableView::Cell::accessoryType() -> AccessoryType {
    return AccessoryType(this->sendMessage<UITableViewCellAccessoryType>("accessoryType"));
}

#endif  //__APPLE__
