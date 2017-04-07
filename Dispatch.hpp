//
//  Dispatch.hpp
//  Jako
//
//  Created by John Zakharov on 20.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef Dispatch_h
#define Dispatch_h

#ifdef __APPLE__
    #include <dispatch/dispatch.h>
#else
    #include "AndroidUtil/AndroidUtil.hpp"
#endif
#include <functional>
#include <map>
#include <mutex>
#include <vector>

namespace Mitsoko{
    
    struct Dispatch{
        
#ifdef __ANDROID__
    protected:
        typedef std::map<int,std::function<void()>> Callbacks;
        static Callbacks callbacks;
        
        static std::mutex callbacksMutex;

        static std::mutex mainThreadHandlersMutex;
        
        static int callbackId;

        static android::os::Handler mainThreadHandler;
    public:
        static void postCallback(int callbackId,bool isMainThread);
        
        /**
          * Creates android.os.Handler object. Should be called once
          * and from main thread only before any 'onMainThread' call.
          */
        static void initMainThreadHandler();
#endif
    public:
        static void onBackground(std::function<void()> functionPointer);
        
        static void onMainThread(std::function<void()> functionPointer);
    };
    
    //  syntax sugar..
    void operator--(std::function<void()> f);
    
    void operator++(std::function<void()> f);
}

#endif /* Dispatch_h */
