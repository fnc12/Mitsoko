//
//  Color.cpp
//  Groozim
//
//  Created by John Zakharov on 17.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Color.hpp"
#include "Mitsoko/AndroidUtil/java/lang/Class.hpp"

#ifdef __ANDROID__

const std::string android::graphics::Color::signature = "android/graphics/Color";

int android::graphics::Color::BLACK() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("BLACK");
    }else{
        return -1;
    }
}

int android::graphics::Color::DKGRAY() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("DKGRAY");
    }else{
        return -1;
    }
}

int android::graphics::Color::GRAY() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("GRAY");
    }else{
        return -1;
    }
}

int android::graphics::Color::LTGRAY() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("LTGRAY");
    }else{
        return -1;
    }
}

int android::graphics::Color::WHITE() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("WHITE");
    }else{
        return -1;
    }
}

int android::graphics::Color::RED() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("RED");
    }else{
        return -1;
    }
}

int android::graphics::Color::GREEN() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("GREEN");
    }else{
        return -1;
    }
}

int android::graphics::Color::BLUE() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("BLUE");
    }else{
        return -1;
    }
}

int android::graphics::Color::YELLOW() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("YELLOW");
    }else{
        return -1;
    }
}

int android::graphics::Color::CYAN() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("CYAN");
    }else{
        return -1;
    }
}

int android::graphics::Color::MAGENTA() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("MAGENTA");
    }else{
        return -1;
    }
}

int android::graphics::Color::TRANSPARENT() {
    if(java::lang::Class cls = java::lang::Class::find<Color>()){
        return cls.getStaticField<int>("TRANSPARENT");
    }else{
        return -1;
    }
}

#endif  //__ANDROID__
