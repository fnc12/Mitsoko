//
//  MapView.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "MapView.hpp"

#ifdef __APPLE__

const std::string MK::MapView::className="MKMapView";

void MK::MapView::addAnnotation(const MK::Annotation &annotation){
    this->sendMessage<void>("addAnnotation:", annotation.handle);
}

void MK::MapView::setRegion(const MK::Coordinate::Region &newValue){
    MKCoordinateRegion r=newValue;
    this->sendMessage<void>("setRegion:", r);
}

MK::Coordinate::Region MK::MapView::region(){
    return this->sendMessage<MKCoordinateRegion>("region");
}

#endif  //__APPLE__
