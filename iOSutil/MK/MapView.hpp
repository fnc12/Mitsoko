
#pragma once

#include "Viper/iOSutil/UI/View.hpp"
#include "Geometry.hpp"

namespace MK {
    struct MapView:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "MKMapView");
        
        void setRegion(const MK::Coordinate::Region &newValue){
            MKCoordinateRegion r=newValue;
            this->sendMessage<void>("setRegion:", r);
        }
        
        MK::Coordinate::Region region(){
            return this->sendMessage<MKCoordinateRegion>("region");
        }
#endif
    };
}
