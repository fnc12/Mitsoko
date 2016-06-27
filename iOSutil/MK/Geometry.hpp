
#pragma once

#ifdef __APPLE__
#import <MapKit/MKGeometry.h>

namespace MK {
    namespace Coordinate{
        
        struct Span:public MKCoordinateSpan{
            Span(MKCoordinateSpan s):MKCoordinateSpan(s){}
            
            static MK::Coordinate::Span Make(CL::Location::Degrees latitudeDelta,CL::Location::Degrees longitudeDelta){
                return MKCoordinateSpanMake(latitudeDelta, longitudeDelta);
            }
        };
        
        struct Region:public MKCoordinateRegion{
            Region(MKCoordinateRegion r):MKCoordinateRegion(r){}
            
            static MK::Coordinate::Region Make(CL::Location::Coordinate2D centerCoordinate, MK::Coordinate::Span span){
                return MKCoordinateRegionMake(centerCoordinate, span);
            }
            
            static MK::Coordinate::Region MakeWithDistance(CL::Location::Coordinate2D centerCoordinate,
                                                           CL::Location::Distance latitudinalMeters,
                                                           CL::Location::Distance longitudinalMeters)
            {
                return MKCoordinateRegionMakeWithDistance(centerCoordinate, latitudinalMeters, longitudinalMeters);
            }
        };
    }
}
#endif
