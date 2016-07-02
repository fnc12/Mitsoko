
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"
#include <functional>
#include <fstream>
#include <iomanip>
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
        struct Callback:Disposable::Observer{
            typedef std::function<void(Image)> type;
            
            type fun;
            bool shouldFire=true;
            Disposable::Id disposableId;
            
            Callback(type fun_,const Disposable &disposable):fun(fun_),disposableId(disposable.id){
                Disposable::subscribe(this);
            }
            
            Callback(const Callback &other):fun(other.fun),shouldFire(other.shouldFire),disposableId(other.disposableId){
                Disposable::subscribe(this);
            }
            
            void operator()(Image image)const{
                if(this->shouldFire){
                    this->fun(image);
                }else{
                    cout<<"shouldFire is false"<<endl;
                }
            }
            
            virtual void disposableDidDispose(Disposable::Id id) override{
                if(id==this->disposableId){
                    this->shouldFire=false;
                }
            }
        };
        
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
        void get(const std::string &url,Callback cb){
            std::string key,filepath;
            if(auto res=getCached(url, &key, &filepath)){
                cb(res);
            }else{
                if(requestRoutine){
                    auto it=this->callbacks.find(url);
                    if(it==this->callbacks.end()){
                        callbacks[url].push_back(cb);
                        ++[=]{
                            if(auto r=requestRoutine){
                                auto imageAsString=std::move(r(url));
                                --[imageAsString=std::move(imageAsString),filepath,key,this,url]{
                                    std::ofstream out(filepath,std::ios::binary);
                                    if(out){
                                        out.write(imageAsString.c_str(), imageAsString.length());
                                        out.close();
                                        auto res=getImageFromFS(filepath);
                                        if(res){
                                            putIntoRAM(key,res);
                                            auto it=this->callbacks.find(url);
                                            if(it != this->callbacks.end()){
                                                for(auto &cb:it->second){
                                                    cb(res);
                                                }
                                                this->callbacks.erase(it);
                                            }else{
                                                std::cerr<<"callback not found for url *"<<url<<"*"<<std::endl;
                                            }
                                        }else{
                                            std::cerr<<"getImageFromFS failed"<<std::endl;
                                        }
                                    }else{
                                        std::cerr<<"unable to save image to file *"<<filepath<<"*"<<std::endl;
                                    }
                                };
                            }
                        };
                    }else{
                        callbacks[url].push_back(cb);
                    }
                }
            }
        }
        
        /**
         *  Returns cached image from RAM or FS or null if one isn't cached.
         *  Doesn't perform request.
         */
        Image getCached(const std::string &url, std::string *keyPointer=nullptr, std::string *filepathPointer=nullptr){
            sha256_t digest;
            ::sha256((unsigned char*)url.c_str(), url.length(), digest);
            auto key=getHexRepresentation(digest, sizeof(digest));
            if(keyPointer){
                *keyPointer=key;
            }
            auto res=getImageFromRAM(key);
            if(res){
//                cb(res);
                return res;
            }else{
                auto filename=this->imageFileName(key);
                auto filepath=this->documentsPath()+'/'+filename;
                if(filepathPointer){
                    *filepathPointer=filepath;
                }
                auto res=getImageFromFS(filepath);
                if(res){
                    putIntoRAM(key, res);
//                    cb(res);
                    return res;
                }else{
                    return {};
                }
            }
        }
            
        
        /**
         *  Documents path is an absolute path of a diretory where client
         *  is able to save cache and other files. Must not have '/' at the end.
         */
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
        std::map<std::string, std::vector<Callback>> callbacks;
        
        void putIntoRAM(const std::string &key,Image image){
#ifdef __APPLE__
            auto keyString=CF::String::create(key);
            this->ramCache()[keyString]=image;
#else
            auto keyString=java::lang::String::create(key);
            this->ramCache().put(keyString,image);
#endif
        }
        
        Image getImageFromRAM(const std::string &key){
#ifdef __APPLE__
            auto keyString=CF::String::create(key);
            return this->ramCache()[keyString].as<UI::Image>();
#else
            auto keyString=java::lang::String::create(key);
            return this->ramCache().get(keyString);
#endif
        }
        
        Image getImageFromFS(const std::string &filepath){
#ifdef __APPLE__
            return UI::Image::createWithContentsOfFile(filepath);
#else
            return android::graphics::BitmapFactory::decodeFile(filepath);
#endif
        }
        
#ifdef __APPLE__
        NS::MutableDictionary _ramCache;
        
        NS::MutableDictionary& ramCache(){
            if(!_ramCache){
                _ramCache=NS::MutableDictionary::create();
            }
            return _ramCache;
        }
#else
        java::util::HashMap<java::lang::String,Image> _ramCache;
        
        decltype(_ramCache)& ramCache(){
            if(!_ramCache){
                cout<<"if(!_ramCache){"<<endl;
                _ramCache=java::util::HashMap<java::lang::String,Image>::create();
//                cout<<"_ramCache=java::util::HashMap<java::lang::String,Image>::create();"<<endl;
                _ramCache.handle=java::lang::JNI::Env()->NewGlobalRef((jobject)_ramCache.handle);
//                cout<<"_ramCache.handle=java::lang::JNI::Env()->NewGlobalRef((jobject)_ramCache.handle);"<<endl;
            }
            return _ramCache;
        }
#endif
        std::string imageFileName(const std::string &key){
            return "image_"+key;
        }
        
        std::string getHexRepresentation(const unsigned char *bytes, size_t length){
            std::ostringstream os;
            os.fill('0');
            os<<std::hex;
            for(const unsigned char * ptr=bytes;ptr<bytes+length;ptr++)
                os<<std::setw(2)<<(unsigned int)*ptr;
            return os.str();
        }
        
        std::string _documentsPath;
    };
}
