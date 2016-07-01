
#pragma once

#include "Viper/AndroidUtil/java/lang/String.hpp"

namespace java {
    namespace io {
        struct File:public java::lang::Object{
            using Object::Object;
#ifdef __ANDROID__
            STATIC_VAR(const std::string, signature, "java/io/File");
            
            static File create(const std::string &path){
                auto p=java::lang::String::create(path);
                return std::move(create(p));
            }
            
            static File create(const java::lang::String &path){
                return std::move(java::lang::Object::create<File>(path));
            }
#endif
        };
    }
}
