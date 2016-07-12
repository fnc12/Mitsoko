
#pragma once

#include "View.hpp"
#include <functional>

namespace UI {
    struct Control:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIControl");
        
        typedef std::function<void(Handle)> Callback;
        
        void setEnabled(bool newValue){
            this->sendMessage<void>("setEnabled:",newValue);
        }
        
        bool enabled(){
            return this->sendMessage<bool>("isEnabled");
        }
        
        void setOnValueChanged(Callback cb){
            if(cb){
                ValueChangedEventHandler::add(this->handle, cb);
                auto cls=NS::getClass("UIControlValueChangedEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(cls,"shared");
                auto sel=sel_getUid("actionDidHappen:");
                this->sendMessage<void>("addTarget:action:forControlEvents:", sharedEventHandler, sel, UIControlEventValueChanged);
            }else{
                ValueChangedEventHandler::remove(this->handle);
            }
        }
        
        struct ValueChangedEventHandler{
            typedef std::map<Handle, Callback> Callbacks;
            STATIC_VAR(Callbacks, callbacks, {});
            
            /**
             *  Assumes *cb* ≠ null.
             */
            static void add(Handle handle,Callback cb){
                auto it=ValueChangedEventHandler::callbacks().find(handle);
                if(it != ValueChangedEventHandler::callbacks().end()){
                    it->second=cb;
                }else{
                    ValueChangedEventHandler::callbacks().insert({handle,cb});
                }
            }
            
            static Callback get(Handle handle){
                auto it=ValueChangedEventHandler::callbacks().find(handle);
                if(it != ValueChangedEventHandler::callbacks().end()){
                    return it->second;
                }else{
                    return {};
                }
            }
            
            static void remove(Handle handle){
                auto it=ValueChangedEventHandler::callbacks().find(handle);
                if(it != ValueChangedEventHandler::callbacks().end()){
                    ValueChangedEventHandler::callbacks().erase(it);
                }else{
//                    ValueChangedEventHandler::callbacks().insert({handle,cb});
                }
            }
            
            static void actionDidHappen(Handle sender){
                if(auto cb=get(sender)){
                    cb(sender);
                }
            }
        };
#endif
    };
}
