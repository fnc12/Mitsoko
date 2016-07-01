
#pragma once

#include "View.hpp"
#include "Viper/iOSutil/NS/Data.hpp"
#include "Viper/iOSutil/CG/CG.hpp"

namespace UI {
    struct Image:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIImage");
        
        static UI::Image create(const std::string &named){
            auto cls=NS::getClass(className());
            auto str=CF::String::create(named);
            return NS::Object::sendMessage<Handle>(cls,"imageNamed:", str.handle);
        }
        
        static UI::Image createWithContentsOfFile(const std::string &filename){
            auto s=CF::String::create(filename);
            return std::move(createWithContentsOfFile(s));
        }
        
        static UI::Image createWithContentsOfFile(const CF::String &filename){
            auto cls=NS::getClass(className());
            return NS::Object::sendMessage<Handle>(cls,"imageWithContentsOfFile:", filename.handle);
        }
        
        static NS::Data JPEGRepresentation(UI::Image image,CG::Float compressionQuality){
            image.retain();
            auto res=CFBridgingRetain(UIImageJPEGRepresentation(CFBridgingRelease(image.handle), CGFloat(compressionQuality)));
            CFRelease(res);
            return res;
        }
        
#endif
    };
}
