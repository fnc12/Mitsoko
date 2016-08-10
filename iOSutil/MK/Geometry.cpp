//
//  Geometry.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Geometry.hpp"

#ifdef __APPLE__

MK::Coordinate::Span::Span(MKCoordinateSpan s):MKCoordinateSpan(s){}

MK::Coordinate::Span MK::Coordinate::Span::make(CL::Location::Degrees latitudeDelta,CL::Location::Degrees longitudeDelta){
    return MKCoordinateSpanMake(latitudeDelta, longitudeDelta);
}

MK::Coordinate::Region::Region(MKCoordinateRegion r):MKCoordinateRegion(r){}

MK::Coordinate::Region MK::Coordinate::Region::make(CL::Location::Coordinate2D centerCoordinate, MK::Coordinate::Span span){
    return MKCoordinateRegionMake(centerCoordinate, span);
}

MK::Coordinate::Region MK::Coordinate::Region::makeWithDistance(CL::Location::Coordinate2D centerCoordinate,
                                                                CL::Location::Distance latitudinalMeters,
                                                                CL::Location::Distance longitudinalMeters)
{
    return MKCoordinateRegionMakeWithDistance(centerCoordinate, latitudinalMeters, longitudinalMeters);
}

#endif
