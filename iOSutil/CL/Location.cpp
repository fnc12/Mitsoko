//
//  Location.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Location.hpp"

#ifdef __APPLE__

CL::Location::Coordinate2D::Coordinate2D(CLLocationCoordinate2D s):CLLocationCoordinate2D(s){}

CL::Location::Coordinate2D CL::Location::Coordinate2D::make(CL::Location::Degrees latitude, CL::Location::Degrees longitude){
    return CLLocationCoordinate2DMake(latitude, longitude);
}

#endif
