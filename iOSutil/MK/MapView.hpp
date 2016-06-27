
#pragma once

#include "Viper/iOSutil/UI/View.hpp"
#include "Geometry.hpp"
#include "Annotation.hpp"

namespace MK {
    struct MapView:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "MKMapView");
        
        void addAnnotation(const MK::Annotation &annotation){
            this->sendMessage<void>("addAnnotation:", annotation.handle);
        }
        
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
