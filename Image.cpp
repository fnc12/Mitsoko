//
//  Image.cpp
//  Groozim
//
//  Created by John Zakharov on 25.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Image.hpp"

#include "Viper/AndroidUtil/java/io/FileOutputStream.hpp"
#include "Viper/AndroidUtil/java/io/File.hpp"
#include "Viper/AndroidUtil/java/io/BufferedOutputStream.hpp"

using java::io::File;
using java::io::BufferedOutputStream;
using java::io::FileOutputStream;

using android::graphics::Bitmap;

Viper::Image::Image():image(){}

Viper::Image::Image(decltype(image) image_):image(image_){}

Viper::Image::operator bool() const {
    return bool(image);
}

Viper::Image::operator decltype(image) () {
    return image;
}

void Viper::Image::writeToFile(const std::string &filepath) {
    
#ifdef __APPLE__
    if(auto i = image) {
        if(auto data = UI::Image::JPEGRepresentation(i, 0.85)) {
            data.writeToFile(filepath, true);
        }
    }
#else
    if(auto i = image) {
        auto file = File::create(filepath);
        auto os = BufferedOutputStream::create(FileOutputStream::create(file));
        i.compress(Bitmap::CompressFormat::JPEG(), 85, os);
        os.close();
    }
#endif  //__APPLE__
}

auto Viper::Image::get() -> decltype(image) {
    return image;
}
