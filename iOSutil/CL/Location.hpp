
#ifndef __VIPER__IOS_UTIL__CL__LOCATION__
#define __VIPER__IOS_UTIL__CL__LOCATION__

#ifdef __APPLE__
#import <CoreLocation/CLLocation.h>

namespace CL {
    struct Location{
        typedef CLLocationDegrees Degrees;
        typedef CLLocationAccuracy Accuracy;
        typedef CLLocationSpeed Speed;
        typedef CLLocationDirection Direction;
        typedef CLLocationDistance Distance;
        
        struct Coordinate2D:public CLLocationCoordinate2D{
            Coordinate2D(CLLocationCoordinate2D s);
            
            static CL::Location::Coordinate2D make(CL::Location::Degrees latitude, CL::Location::Degrees longitude);
        };
    };
}

#endif  //__APPLE__

#endif  //__VIPER__IOS_UTIL__CL__LOCATION__
