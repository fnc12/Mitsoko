
#pragma once

#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

#include <functional>
#include <fstream>
#include <iomanip>

#include "sha256.hpp"
#include "Dispatch.hpp"
#include "Viper/Image.hpp"

namespace Viper {
    
    struct ImageCache{
        
        static ImageCache shared;
        
/*#ifdef __APPLE__
        typedef UI::Image Image;
#else
        typedef android::graphics::Bitmap Image;
#endif*/
        struct Callback : Disposable::Observer {
            typedef std::function<void(Image)> type;
            
            type fun;
            bool shouldFire=true;
            Disposable::Id disposableId;
            
            Callback(type fun_,const Disposable &disposable);
            
            Callback(const Callback &other);
            
            void operator()(Image image) const;
            
            virtual void disposableDidDispose(Disposable::Id id) override;
        };
        
        /**
         *  This is a point where ImageCache interacts with external lib for
         *  url request or anything else to request an image from server.
         *  The only argument is an image url. Return value is an image got 
         *  from std::stringstream.
         *  This routine called from background thread and must not dispatch functions
         *  to other threads.
         */
//        std::function<std::string(const std::string&)> requestRoutine;
        
        /**
         *  Should be called from main thread only. Otherwise data races may occur.
         */
        void get(const std::string &url, Callback cb);
        
        /**
         *  Returns cached image from RAM or FS or null if one isn't cached.
         *  Doesn't perform request.
         */
        Viper::Image getCached(const std::string &url, std::string *keyPointer = nullptr, std::string *filepathPointer = nullptr);
            
        
        /**
         *  Documents path is an absolute path of a diretory where client
         *  is able to save cache and other files. Must not have '/' at the end.
         */
        void documentsPath(const std::string &newValue);
        
        const std::string& documentsPath();
        
    protected:
        std::map<std::string, std::vector<Callback>> callbacks;
        
        void putIntoRAM(const std::string &key,Image image);
        
        Image getImageFromRAM(const std::string &key);
        
        Image getImageFromFS(const std::string &filepath);
        
#ifdef __APPLE__
        NS::MutableDictionary _ramCache;
        
        NS::MutableDictionary& ramCache();
#else
        java::util::HashMap<java::lang::String, android::graphics::Bitmap> _ramCache;
        
        decltype(_ramCache)& ramCache();
#endif
        std::string imageFileName(const std::string &key);
        
        std::string getHexRepresentation(const unsigned char *bytes, size_t length);
        
        std::string _documentsPath;
    };
}
