//
//  ImageCache.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ImageCache.hpp"
#include "Viper/Url/Request.hpp"

#include <iostream>

Viper::ImageCache Viper::ImageCache::shared;

Viper::ImageCache::Callback::Callback(type fun_,const Disposable &disposable):fun(fun_),disposableId(disposable.id){
    Disposable::subscribe(this);
}

Viper::ImageCache::Callback::Callback(const Callback &other):fun(other.fun),shouldFire(other.shouldFire),disposableId(other.disposableId){
    Disposable::subscribe(this);
}

void Viper::ImageCache::Callback::operator()(Image image) const{
    if(this->shouldFire){
        this->fun(image);
    }else{
        std::cerr<<"shouldFire is false"<<std::endl;
    }
}

void Viper::ImageCache::Callback::disposableDidDispose(Disposable::Id id){
    if(id==this->disposableId){
        this->shouldFire=false;
    }
}

void Viper::ImageCache::get(const std::string &url, Callback cb){
    std::string key, filepath;
    if(auto res = getCached(url, &key, &filepath)){
        cb(res);
    }else{
        auto it = this->callbacks.find(url);
        if(it == this->callbacks.end()){
            callbacks[url].push_back(cb);
            Url::Request request;
            request.url(url);
            request.performAsync<Image>([=](Url::Response response, Viper::Image image, Url::Error error) {
                if(image) {
                    image.writeToFile(filepath);
                    putIntoRAM(key, image);
                    auto it = this->callbacks.find(url);
                    if(it != this->callbacks.end()) {
                        for(auto &cb : it->second) {
                            cb(image);
                        }
                        this->callbacks.erase(it);
                    }else{
                        std::cerr << "callback not found for url *" << url << "*" << std::endl;
                    }
                }else{
                    std::cerr << "image is null for url *" << url << "*" << std::endl;
                }
            });
        }else{
            callbacks[url].push_back(cb);
        }
    }
}

void Viper::ImageCache::put(const std::string &url, Image image) {
    auto key = this->keyByUrl(url);
    auto filename = this->imageFileName(key);
    auto filepath = this->documentsPath() + '/' + filename;
    image.writeToFile(filepath);
    putIntoRAM(key, image);
}

Viper::Image Viper::ImageCache::getCached(const std::string &url, std::string *keyPointer, std::string *filepathPointer) {
    /*sha256_t digest;
    ::sha256((unsigned char*)url.c_str(), url.length(), digest);
    auto key = getHexRepresentation(digest, sizeof(digest));*/
    auto key = this->keyByUrl(url);
    if(keyPointer){
        *keyPointer = key;
    }
    auto res = getImageFromRAM(key);
    if(res){
        return res;
    }else{
        auto filename = this->imageFileName(key);
        auto filepath = this->documentsPath() + '/' + filename;
        if(filepathPointer) {
            *filepathPointer = filepath;
        }
        auto res = getImageFromFS(filepath);
        if(res) {
            putIntoRAM(key, res);
            return res;
        }else{
            return {};
        }
    }
}

std::string Viper::ImageCache::keyByUrl(const std::string &url) const {
    sha256_t digest;
    ::sha256((unsigned char*)url.c_str(), url.length(), digest);
    return getHexRepresentation(digest, sizeof(digest));
}

void Viper::ImageCache::documentsPath(const std::string &newValue){
    _documentsPath=newValue;
}

const std::string& Viper::ImageCache::documentsPath(){
    if(_documentsPath.empty()){
#ifdef __APPLE__
        NSString *dp = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
        _documentsPath=dp.UTF8String;
#else
        _documentsPath = "/data/data/" + java::lang::JNI::appId;
#endif
    }
    return _documentsPath;
}

void Viper::ImageCache::putIntoRAM(const std::string &key, Image image){
#ifdef __APPLE__
    auto keyString = CF::String::create(key);
    this->ramCache()[keyString] = image.get();
#else
    auto keyString = java::lang::String::create(key);
    this->ramCache().put(keyString, image.get());
#endif
}

Viper::Image Viper::ImageCache::getImageFromRAM(const std::string &key) {
#ifdef __APPLE__
    auto keyString = CF::String::create(key);
    return this->ramCache()[keyString].as<UI::Image>();
#else
    auto keyString = java::lang::String::create(key);
    return this->ramCache().get(keyString);
#endif
}

auto Viper::ImageCache::getImageFromFS(const std::string &filepath) -> Image {
#ifdef __APPLE__
    return UI::Image::createWithContentsOfFile(filepath);
#else
    return android::graphics::BitmapFactory::decodeFile(filepath);
#endif
}

#ifdef __APPLE__

NS::MutableDictionary& Viper::ImageCache::ramCache(){
    if(!_ramCache){
        _ramCache = NS::MutableDictionary::create();
    }
    return _ramCache;
}

#else

auto Viper::ImageCache::ramCache()->decltype(_ramCache)&{
    if(!_ramCache){
        _ramCache = java::util::HashMap<java::lang::String, android::graphics::Bitmap>::create();
        _ramCache.handle = java::lang::JNI::Env()->NewGlobalRef((jobject)_ramCache.handle);
    }
    return _ramCache;
}

#endif

std::string Viper::ImageCache::imageFileName(const std::string &key){
    return "image_"+key;
}

std::string Viper::ImageCache::getHexRepresentation(const unsigned char *bytes, size_t length) const {
    std::ostringstream os;
    os.fill('0');
    os << std::hex;
    for(const unsigned char * ptr = bytes; ptr < bytes + length; ptr++)
        os << std::setw(2) << (unsigned int)*ptr;
    return os.str();
}
