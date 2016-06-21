
#pragma once

#include "View.hpp"

namespace UI {
    struct ActionSheet:public UI::View{
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIActionSheet");
        
        typedef std::function<void(UI::ActionSheet,int)> ClickedButtonAtIndex;
        typedef std::function<void(UI::ActionSheet,int)> WillDismissWithButtonIndex;
        typedef std::function<void(UI::ActionSheet,int)> DidDismissWithButtonIndex;
        
        static UI::ActionSheet create(){
            return NS::Object::create<UI::ActionSheet>();
        }
        
        void setDidDismissWithButtonIndex(DidDismissWithButtonIndex f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIActionSheetDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).didDismissWithButtonIndex=f;
        }
        
        void setWillDismissWithButtonIndex(WillDismissWithButtonIndex f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIActionSheetDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).willDismissWithButtonIndex=f;
        }
        
        void setClickedButtonAtIndex(ClickedButtonAtIndex f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIActionSheetDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).clickedButtonAtIndex=f;
        }
        
        void showInView(const UI::View &view){
            this->sendMessage<void>("showInView:", view.handle);
        }
        
        void setDestructiveButtonIndex(int newValue){
            this->sendMessage<void>("setDestructiveButtonIndex:", NSInteger(newValue));
        }
        
        int destructiveButtonIndex(){
            return int(this->sendMessage<NSInteger>("destructiveButtonIndex"));
        }
        
        void setCancelButtonIndex(int newValue){
            this->sendMessage<void>("setCancelButtonIndex:", NSInteger(newValue));
        }
        
        int cancelButtonIndex(){
            return int(this->sendMessage<NSInteger>("cancelButtonIndex"));
        }
        
        int numberOfButtons(){
            return int(this->sendMessage<NSInteger>("numberOfButtons"));
        }
        
        NS::String buttonTitleAtIndex(int index){
            return this->sendMessage<Handle>("buttonTitleAtIndex:", NSInteger(index));
        }
        
        int addButtonWithTitle(const std::string &t){
            auto str=CF::String::create(t);
            return this->addButtonWithTitle(str);
        }
        
        int addButtonWithTitle(const CF::String &t){
            return int(this->sendMessage<NSInteger>("addButtonWithTitle:", t.handle));
        }
        
        void setTitle(const std::string &newValue){
            auto str=CF::String::create(newValue);
            this->setTitle(str);
        }
        
        void setTitle(const CF::String &newValue){
            this->sendMessage<void>("setTitle:", newValue.handle);
        }
        
        std::string title(){
            NS::String res=this->sendMessage<Handle>("title");
            return res.UTF8String();
        }
        
        /**
         *  Class which implements all UIActionSheetDelegate callbacks.
         *  Instance is created and stored per one UI::ActionSheet after user assigns
         *  any callback to UI::ActionSheet instance.
         */
        struct DelegateEventHandler{
            typedef std::map<Handle, DelegateEventHandler> DelegateEventHandlersMap;
            STATIC_VAR(DelegateEventHandlersMap, delegateEventHandlers, {});
            
            ClickedButtonAtIndex clickedButtonAtIndex;
            WillDismissWithButtonIndex willDismissWithButtonIndex;
            DidDismissWithButtonIndex didDismissWithButtonIndex;
            
            static DelegateEventHandler& getOrCreate(const void *as){
                auto it=delegateEventHandlers().find(as);
                if(it != delegateEventHandlers().end()){
                    return it->second;
                }else{
                    return delegateEventHandlers().insert({as,{}}).first->second;
                }
            }
            
            static DelegateEventHandler* get(const void *as){
                auto it=delegateEventHandlers().find(as);
                if(it != delegateEventHandlers().end()){
                    return &it->second;
                }else{
                    return nullptr;
                }
            }
            
            static void remove(const void *as){
                auto it=delegateEventHandlers().find(as);
                if(it != delegateEventHandlers().end()){
                    delegateEventHandlers().erase(it);
                }
            }
            
            static void actionSheetDidDismissWithButtonIndex(const void *as,int buttonIndex){
                if(auto e=get(as)){
                    if(e->didDismissWithButtonIndex){
                        e->didDismissWithButtonIndex(as,buttonIndex);
                    }
                    
                    //  expliclty specifying class name cause there is int remove(const char *) function
                    //  in C standard library..
                    DelegateEventHandler::remove(as);
                }
            }
            
            static void actionSheetWillDismissWithButtonIndex(const void *as,int buttonIndex){
                if(auto e=get(as)){
                    if(e->willDismissWithButtonIndex){
                        e->willDismissWithButtonIndex(as,buttonIndex);
                    }
                }
            }
            
            static void actionSheetClickedButtonAtIndex(const void *as,int buttonIndex){
                if(auto e=get(as)){
                    if(e->clickedButtonAtIndex){
                        e->clickedButtonAtIndex(as,buttonIndex);
                    }
                }
            }
        };
#endif
    };
}