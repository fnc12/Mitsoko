//
//  Image.cpp
//  Groozim
//
//  Created by John Zakharov on 25.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Image.hpp"

#include "Mitsoko/AndroidUtil/java/io/FileOutputStream.hpp"
#include "Mitsoko/AndroidUtil/java/io/File.hpp"
#include "Mitsoko/AndroidUtil/java/io/BufferedOutputStream.hpp"

#include <iostream>

#include "Services/Storage.hpp"

using Services::Storage;

static void addToLog(const std::string &line) {
    auto testData = Storage::shared().testData();
    testData.push_back(line);
    Storage::shared().setTestData(std::move(testData));
}

using java::io::File;
using java::io::BufferedOutputStream;
using java::io::FileOutputStream;

using android::graphics::Bitmap;

Mitsoko::Image::Image():image(){}

Mitsoko::Image::Image(decltype(image) image_):image(image_){}

Mitsoko::Image::operator bool() const {
    return bool(image);
}

Mitsoko::Image::operator decltype(image) () {
    return image;
}

void Mitsoko::Image::writeToFile(const std::string &filepath) {
    
#ifdef __APPLE__
    if(auto i = image) {
        addToLog("if(auto i = image) {");
        if(auto data = UI::Image::JPEGRepresentation(i, 0.85)) {
            addToLog("if(auto data = UI::Image::JPEGRepresentation(i, 0.85)) {");
            auto done = data.writeToFile(filepath, true);
            addToLog("auto done = data.writeToFile(filepath, true);");
            addToLog("done = " + std::to_string(done));
            if(!done) {
                std::cerr << "Viper::Image: write to file failed" << std::endl;
            }
        }
    }
#else
    if(auto i = image) {
        auto file = File::create(filepath);
        auto os = BufferedOutputStream::create(FileOutputStream::create(file));
        auto compressFormat = Bitmap::CompressFormat::JPEG();
        i.compress(compressFormat, 85, os);
        os.close();
    }
#endif  //__APPLE__
}

auto Mitsoko::Image::get() -> decltype(image) {
    return image;
}
