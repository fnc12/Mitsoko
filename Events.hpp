
#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <memory>

namespace Viper {

    struct EventBase{
        typedef const void *EventId;
        
//        virtual void v(){}
        virtual ~EventBase()=default;
        
//    protected:
        
        static std::map<EventId, std::shared_ptr<EventBase>>& events(){
            static std::map<EventId, std::shared_ptr<EventBase>> res;
            return res;
        }
    };
    
    template<class ...Args>
    struct Event:public EventBase{
        std::function<void(Args...)> f;
        
        Event(decltype(f) f_):f(f_){}
        
        operator bool()const{
            return bool(this->f);
        }
        
        void operator()(Args ...args){
            f(args...);
        }
    };
    
    template<class ...Args>
    struct EventProxy{
        typedef std::function<void(Args...)> function_type;
        
        EventProxy& operator=(function_type f){
            if(this->assignCallback){
                this->assignCallback(f);
            }
            return *this;
        }
        
        std::function<void(function_type)> assignCallback;
    };
    
    template<class ...Args>
    inline EventBase::EventId registerEvent(EventBase::EventId eventId,Event<Args...> event){
        if(event){
            auto eventPointer=std::make_shared<decltype(event)>(event);
            auto it=EventBase::events().find(eventId);
            if(it != EventBase::events().end()){
                it->second=std::dynamic_pointer_cast<EventBase>(eventPointer);
            }else{
                EventBase::events().insert({eventId,std::dynamic_pointer_cast<EventBase>(eventPointer)});
            }
        }else{
            auto it=EventBase::events().find(eventId);
            if(it != EventBase::events().end()){
                EventBase::events().erase(it);
            }else{
//                EventBase::events().insert({eventId,std::dynamic_pointer_cast<EventBase>(event)});
            }
        }
        return eventId;
    }
    
    inline void alertViewWillDismissWithButtonIndex(const void *alertView,int buttonIndex){
        
    }
    
    inline void alertViewClickedButtonAtIndex(const void *alertView,int buttonIndex){
        auto it=EventBase::events().find(alertView);
        if(it != EventBase::events().end()){
            auto eventBasePointer=it->second.get();
            if(auto event=static_cast<Event<const void*,int>*>(eventBasePointer)){
                (*event)(alertView,buttonIndex);
            }
        }
    }

}
