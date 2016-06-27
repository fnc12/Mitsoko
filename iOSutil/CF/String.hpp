
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include <experimental/optional>

namespace CF {
    struct String:public NS::Object{
        using Object::Object;
#ifdef __APPLE__
        
        static String create(std::experimental::optional<std::string> str){
            if(str){
                return std::move(create(*str));
            }else{
                return {};
            }
        }
        
        static String create(const std::string &str){
            return std::move(create(str.c_str()));
        }
        
        static String create(const char *cString){
            auto cfStr=CFStringCreateWithCString(nullptr, cString, kCFStringEncodingUTF8);
            String res(cfStr);
//            res.shouldClearOnDestroy=true;
            return std::move(res);
        }
#endif
    };
}
