
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
            sha256_t digest;
            ::sha256((unsigned char*)url.c_str(), url.length(), digest);
            auto key=getHexRepresentation(digest, sizeof(digest));
#ifdef __APPLE__
            auto keyString=CF::String::create(key);
            if(auto res=this->ramCache()[keyString].as<UI::Image>()){
#else
            auto keyString=java::lang::String::create(key);
//            java::lang::JNI::Env()->ExceptionCheck();
//            cout<<"keyString = "<<keyString.c_str()<<endl;
//            auto c=this->ramCache();
//            cout<<"auto c=this->ramCache();"<<endl;
//            java::lang::JNI::Env()->ExceptionCheck();
//            cout<<"auto c=this->ramCache();"<<endl;
            if(auto res=this->ramCache().get(keyString)){
//            if(false){
#endif
//                cb(res);
            }else{
                auto filename=this->imageFileName(key);
                auto filepath=this->documentsPath()+'/'+filename;
//                cout<<"filepath = "<<filepath<<endl;
#ifdef __APPLE__
                if(auto res=UI::Image::createWithContentsOfFile(filepath)){
#else
//                java::util::HashMap<java::lang::Object,java::lang::Object>::create();
                if(auto res=android::graphics::BitmapFactory::decodeFile(filepath)){
#endif
#ifdef __APPLE__
                    this->ramCache()[keyString]=res;
#else
//                    cout<<"this->ramCache().put(keyString,res);"<<endl;
                    this->ramCache().put(keyString,res);
#endif
                    cb(res);
                }else{
//                    cout<<"requestRoutine = "<<bool(requestRoutine)<<endl;
                    if(requestRoutine){
//                        cout<<"if(requestRoutine){"<<endl;
                        auto it=this->callbacks.find(url);
                        if(it==this->callbacks.end()){
                            callbacks[url].push_back(cb);
                            ++[=]{
                                if(auto r=requestRoutine){
                                    auto imageAsString=std::move(r(url));
                                    --[imageAsString=std::move(imageAsString),filepath,keyString,this,url]{
//                                        cout<<"imageAsString length = "<<imageAsString.length()<<endl;
                                        std::ofstream out(filepath,std::ios::binary);
                                        if(out){
                                            out.write(imageAsString.c_str(), imageAsString.length());
                                            out.close();
//                                            cout<<"file wrote"<<endl;
#ifdef __APPLE__
                                            if(auto res=UI::Image::createWithContentsOfFile(filepath)){
                                                _ramCache[keyString]=res;
#else
                                            if(auto res=android::graphics::BitmapFactory::decodeFile(filepath)){
                                                _ramCache.put(keyString,res);
//                                                cout<<"put done"<<endl;
#endif
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
                                                cout<<"decode failed"<<endl;
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
                cout<<"_ramCache=java::util::HashMap<java::lang::String,Image>::create();"<<endl;
                _ramCache.handle=java::lang::JNI::Env()->NewGlobalRef((jobject)_ramCache.handle);
                cout<<"_ramCache.handle=java::lang::JNI::Env()->NewGlobalRef((jobject)_ramCache.handle);"<<endl;
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
