
#pragma once

#include "View.hpp"
#include "Viper/iOSutil/CF/String.hpp"
#include "Viper/iOSutil/NS/String.hpp"
#include "TextField.hpp"
#include <experimental/optional>
#include <initializer_list>
#include <map>
#include <functional>
//#include "Viper/Events.hpp"

namespace UI {
    struct AlertView:public UI::View{
        typedef UI::View Super;
        using View::View;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIAlertView");
        
        typedef std::function<void(UI::AlertView,int)> ClickedButtonAtIndex;
        typedef std::function<void(UI::AlertView,int)> WillDismissWithButtonIndex;
        typedef std::function<void(UI::AlertView,int)> DidDismissWithButtonIndex;
        
        void setDidDismissWithButtonIndex(DidDismissWithButtonIndex f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIAlertViewDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).didDismissWithButtonIndex=f;
        }
        
        void setWillDismissWithButtonIndex(WillDismissWithButtonIndex f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIAlertViewDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).willDismissWithButtonIndex=f;
        }
        
        void setClickedButtonAtIndex(ClickedButtonAtIndex f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIAlertViewDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).clickedButtonAtIndex=f;
        }
        
        enum class Style{
            Default=UIAlertViewStyleDefault,
            SecureTextInput=UIAlertViewStyleSecureTextInput,
            PlainTextInput=UIAlertViewStylePlainTextInput,
            LoginAndPasswordInput=UIAlertViewStyleLoginAndPasswordInput,
        };
        
        void setMessage(std::experimental::optional<std::string> newValue){
            auto str=CF::String::create(newValue);
            this->setMessage(str);
        }
        
        void setMessage(const CF::String &newValue){
            this->sendMessage<void>("setMessage:", newValue.handle);
        }
        
        std::string message(){
            NS::String res=this->sendMessage<Handle>("message");
            return res.UTF8String();
        }
        
        int addButtonWithTitle(const std::string &title){
            auto t=CF::String::create(title);
            return this->addButtonWithTitle(t);
        }
        
        int addButtonWithTitle(const CF::String &title){
            return int(this->sendMessage<NSInteger>("addButtonWithTitle:", title.handle));
        }
        
        void setCancelButtonIndex(int newValue){
            this->sendMessage<void>("setCancelButtonIndex:", NSInteger(newValue));
        }
        
        int cancelButtonIndex(){
            return int(this->sendMessage<NSInteger>("cancelButtonIndex"));
        }
        
        void setAlertViewStyle(Style newValue){
            this->sendMessage<void>("setAlertViewStyle:", UIAlertViewStyle(newValue));
        }
        
        Style alertViewStyle(){
            return Style(this->sendMessage<UIAlertViewStyle>("alertViewStyle"));
        }
        
        void setTitle(const std::string &newValue){
            auto v=CF::String::create(newValue);
            this->setTitle(v);
        }
        
        void setTitle(const CF::String &newValue){
            this->sendMessage<void>("setTitle:", newValue.handle);
        }
        
        std::string title(){
            NS::String res=this->sendMessage<Handle>("title");
            return res.UTF8String();
        }
        
        void show(){
            this->sendMessage<void>("show");
        }
        
        UI::TextField textFieldAtIndex(int index){
            return this->sendMessage<Handle>("textFieldAtIndex:", NSInteger(index));
        }
        
        
        
        static AlertView create(std::experimental::optional<std::string> title,
                                std::experimental::optional<std::string> message,
                                std::experimental::optional<std::string> cancelButtonTitle,
                                std::initializer_list<std::string> otherButtonTitles={})
        {
            return std::move(create(CF::String::create(title),
                                    CF::String::create(message),
                                    CF::String::create(cancelButtonTitle),
                                    std::move(otherButtonTitles)));
        }
        
        static AlertView create(const CF::String &title,
                                const CF::String &message,
                                const CF::String &cancelButtonTitle,
                                std::initializer_list<std::string> otherButtonTitles={})
        {
            auto cls=NS::getClass(className());
            if(cls){
                auto res=NS::Object::create<AlertView>();
                res.setTitle(title);
                res.setMessage(message);
                if(cancelButtonTitle){
                    res.setCancelButtonIndex(res.addButtonWithTitle(cancelButtonTitle));
                }
                for(const auto &t:otherButtonTitles){
                    auto s=CF::String::create(t);
                    res.addButtonWithTitle(s);
                }
                return std::move(res);
            }else{
                return {};
            }
        }
        
        /**
         *  Class which implements all UIAlertViewDelegate callbacks. 
         *  Instance is created and stored per one UI::AlertView after user assigns
         *  any callback to UI::AlertView instance.
         */
        struct DelegateEventHandler{
            typedef std::map<Handle, DelegateEventHandler> DelegateEventHandlersMap;
            STATIC_VAR(DelegateEventHandlersMap, delegateEventHandlers, {});
            
            ClickedButtonAtIndex clickedButtonAtIndex;
            WillDismissWithButtonIndex willDismissWithButtonIndex;
            DidDismissWithButtonIndex didDismissWithButtonIndex;
            
            static DelegateEventHandler& getOrCreate(const void *aw){
                auto it=delegateEventHandlers().find(aw);
                if(it != delegateEventHandlers().end()){
                    return it->second;
                }else{
                    return delegateEventHandlers().insert({aw,{}}).first->second;
                }
            }
            
            static DelegateEventHandler* get(const void *aw){
                auto it=delegateEventHandlers().find(aw);
                if(it != delegateEventHandlers().end()){
                    return &it->second;
                }else{
                    return nullptr;
                }
            }
            
            static void remove(const void *aw){
                auto it=delegateEventHandlers().find(aw);
                if(it != delegateEventHandlers().end()){
                    delegateEventHandlers().erase(it);
                }
            }
            
            static void alertViewDidDismissWithButtonIndex(const void *aw,int buttonIndex){
                if(auto e=get(aw)){
                    if(e->didDismissWithButtonIndex){
                        e->didDismissWithButtonIndex(aw,buttonIndex);
                    }
                    
                    //  expliclty specifying class name cause there is int remove(const char *) function
                    //  in C standard library..
                    DelegateEventHandler::remove(aw);
                }
            }
            
            static void alertViewWillDismissWithButtonIndex(const void *aw,int buttonIndex){
                if(auto e=get(aw)){
                    if(e->willDismissWithButtonIndex){
                        e->willDismissWithButtonIndex(aw,buttonIndex);
                    }
                }
            }
            
            static void alertViewClickedButtonAtIndex(const void *aw,int buttonIndex){
                if(auto e=get(aw)){
                    if(e->clickedButtonAtIndex){
                        e->clickedButtonAtIndex(aw,buttonIndex);
                    }
                }
            }
        };
#endif
    };
}
