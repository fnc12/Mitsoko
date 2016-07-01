
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"
#include <functional>
#include <fstream>
#include "sha256.hpp"
#include "Dispatch.hpp"

namespace Viper {
    struct ImageCache{
        static ImageCache& shared(){
            static ImageCache res;
            return res;
        }
#ifdef __APPLE__
        typedef UI::Image Image;
#else
        typedef android::graphics::Bitmap Image;
#endif
        
        /**
         *  This is a point where ImageCache interacts with external lib for
         *  url request or anything else to request an image from server.
         *  The only argument is an image url. Return value is an image got 
         *  from std::stringstream.
         *  This routine called from background thread and must not dispatch functions
         *  to other threads.
         */
        std::function<std::string(const std::string&)> requestRoutine;
        
        /**
         *  Should be called from main thread only. Otherwise data races may occur.
         */
#ifdef __APPLE__
        void get(const std::string &url,std::function<void(Image)> cb){
            auto key = ::shaString(url);
            auto keyString=CF::String::create(key);
#ifdef __APPLE__
            if(auto res=this->ramCache()[keyString].as<UI::Image>()){
#else
                
#endif
                cb(res);
            }else{
                auto filename=this->imageFileName(key);
#ifdef __APPLE__
                if(auto res=UI::Image::createWithContentsOfFile(filename)){
#else
                    
#endif
                    cb(res);
                }else{
                    if(requestRoutine){
                        ++[=]{
                            if(auto r=requestRoutine){
                                auto imageAsString=std::move(r(url));
                                --[imageAsString=std::move(imageAsString),filename]{
                                    cout<<"imageAsString length = "<<imageAsString.length()<<endl;
                                    std::ofstream out(filename,std::ios::binary);
                                    if(out){
                                        out.write(imageAsString.c_str(), imageAsString.length());
                                        out.close();
                                    }else{
                                        std::cerr<<"unable to save image to file *"<<filename<<"*"<<std::endl;
                                    }
                                };
                            }
                        };
                    }
                }
            }
        }
#else
        
#endif
        
        void documentsPath(const std::string &newValue){
            _documentsPath=newValue;
        }
        
        const std::string& documentsPath(){
            if(_documentsPath.empty()){
#ifdef __APPLE__
                NSString *dp=NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
                _documentsPath=dp.UTF8String;
#else
                _documentsPath="/data/data/"+java::lang::JNI::appId();
#endif
            }
            return _documentsPath;
        }
        
    protected:
#ifdef __APPLE__
        NS::MutableDictionary _ramCache;
        
        NS::MutableDictionary& ramCache(){
            if(!_ramCache){
                _ramCache=NS::MutableDictionary::create();
            }
            return _ramCache;
        }
        
        std::string imageFileName(const std::string &key){
            return "image_"+key;
        }
#else
        
#endif
        std::string _documentsPath;
    };
}
