
#ifndef __VIPER__IOS_UTIL__UI__IMAGE__
#define __VIPER__IOS_UTIL__UI__IMAGE__

#include "View.hpp"
#include "Viper/iOSutil/NS/Data.hpp"
#include "Viper/iOSutil/CG/Size.hpp"

namespace UI {
    struct Image:public NS::Object{
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UIImage");
        
        static UI::Image create(const std::string &named);
        
        static UI::Image createWithContentsOfFile(const std::string &filename);
        
        static UI::Image createWithContentsOfFile(const CF::String &filename);
        
        static NS::Data JPEGRepresentation(UI::Image image,CG::Float compressionQuality);
        
        CG::Size size();
        
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__IMAGE__
