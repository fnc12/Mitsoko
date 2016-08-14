
#ifndef __VIPER__IOS_UTIL__UI__CONTROL__
#define __VIPER__IOS_UTIL__UI__CONTROL__

#include "View.hpp"
#include "Viper/Util.hpp"
#include <functional>
#include <map>

namespace UI {
    struct Control:public UI::View{
        using View::View;

#ifdef __APPLE__
        
        static const std::string className;
//        STATIC_VAR(const std::string, className, "UIControl");
        
        typedef std::function<void(Handle)> Callback;
        
        void setEnabled(bool newValue);
        
        bool enabled();
        
        void setOnValueChanged(Callback cb);
        
        struct ValueChangedEventHandler{
            typedef std::map<Handle, Callback> Callbacks;
            static Callbacks callbacks;
//            STATIC_VAR(Callbacks, callbacks, {});
            
            /**
             *  Assumes *cb* ≠ null.
             */
            static void add(Handle handle,Callback cb);
            
            static Callback get(Handle handle);
            
            static void remove(Handle handle);
            
            static void actionDidHappen(Handle sender);
        };
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__CONTROL__
