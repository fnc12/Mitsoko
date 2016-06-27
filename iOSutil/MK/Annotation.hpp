
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/iOSutil/NS/MutableDictionary.hpp"
#include <experimental/optional>
#include <iostream>
//#include "Viper/Disposable.hpp"

namespace MK {
    struct Annotation:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        
        static MK::Annotation create(/*const Viper::Disposable &disposable,*/
                                     CL::Location::Coordinate2D coordinate,
                                     std::experimental::optional<std::string> title={},
                                     std::experimental::optional<std::string> subtitle={})
        {
//            if(auto cls=NS::getClass("ViperMKAnnotation")){
//                NS::MutableDictionary all=NS::Object::sendMessage<Handle>(cls, "all");
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
            /*}else{
                std::cout<<"ViperMKAnnotation class is nil"<<std::endl;
                return {};
            }*/
        }
        
    protected:
        
        /*struct Observer:public Viper::Disposable::Observer{
            STATIC_VAR(Observer, shared, {});
            
            virtual void disposableDidDispose(Viper::Disposable::Id id) override{
                
            }
        };*/
#endif
    };
}
