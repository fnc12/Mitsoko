
#pragma once

#ifdef __APPLE__
#import <CoreLocation/CLLocation.h>

namespace CL {
    namespace Location{
        typedef CLLocationDegrees Degrees;
        typedef CLLocationAccuracy Accuracy;
        typedef CLLocationSpeed Speed;
        typedef CLLocationDirection Direction;
        typedef CLLocationDistance Distance;
        
        struct Coordinate2D:public CLLocationCoordinate2D{
            Coordinate2D(CLLocationCoordinate2D s):CLLocationCoordinate2D(s){}
            
            static CL::Location::Coordinate2D Make(CL::Location::Degrees latitude, CL::Location::Degrees longitude){
                return CLLocationCoordinate2DMake(latitude, longitude);
            }
        };
    }
}

#endif
