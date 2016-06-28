
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/iOSutil/NS/MutableDictionary.hpp"
#include <experimental/optional>
#include <iostream>

namespace MK {
    struct Annotation:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        
        static MK::Annotation create(CL::Location::Coordinate2D coordinate,
                                     std::experimental::optional<std::string> title={},
                                     std::experimental::optional<std::string> subtitle={})
        {
            if(auto newAnnotation=NS::Object::create<Annotation>("ViperMKAnnotation")){
                newAnnotation.sendMessage<void>("setCoordinate:", CLLocationCoordinate2D(coordinate));
                auto t=CF::String::create(title);
                newAnnotation.sendMessage<void>("setTitle:", t.handle);
                auto s=CF::String::create(subtitle);
                newAnnotation.sendMessage<void>("setSubtitle:", s.handle);
                return newAnnotation;
            }else{
                std::cout<<"newAnnotation is nil"<<std::endl;
                return {};
            }
        }
#endif
    };
}
