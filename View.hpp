//
//  View.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef View_h
#define View_h

#include <memory>
#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include <functional>

#include "Disposable.hpp"
#include "ViewPresenterIF.hpp"
#include "ImageCache.hpp"
#include "Language.hpp"
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

#define VIEW_DECL(module) struct View:public Viper::View<module::EventHandler, module::UserInterface>,Selfish<View>

/**
 *  Used fo simplifying client member references declaration.
 */
#ifdef __APPLE__
#define FIELD_DECL(type,name) type name(){return NS::Object::sendMessage<Handle>(this->handle,#name);}
#else
#define FIELD_DECL(type,name) type name(){return java::lang::Object(this->handle).getField<type>(#name);}
#endif

namespace Viper{
    
    struct ViewBase{
        
        const void *handle = nullptr;
        
//        ViewBase(decltype(handle)handle_);
//        ViewBase(const ViewBase&) = delete;
        
        virtual ~ViewBase();
        
//        virtual void willAppear()=0;
//        virtual void didAppear()=0;
//        virtual void willDisappear()=0;
        
        std::function<void()> willAppear;
        std::function<void()> didAppear;
        std::function<void()> willDisappear;
        
//        typedef std::map<std::string,std::string> Arguments;
        
        virtual void messageReceived(int messageCode, std::string args) {};
        
        virtual void onActivityResult(int requestCode, int resultCode, android::content::Intent data);
        
    protected:
        
        /**
         *  Adapter ids of table- or listviews in current view. If you want its adapters to be removed
         *  from memory properly you have to either setAdapter({}) or add adapter id into this
         *  vector and it will be cleared in destructor. You can obtain adapter id as a returned value
         *  from *setAdapter* function in **UI::TableView** or **android::widget::ListView**.
         */
        std::vector<TableListAdapter::AdapterId> adapterIds;
    };
    
    //  base class for view..
//    template<class EH,class UI>
    struct View:public ViewBase,public Disposable/*,public UI*/{
//        std::shared_ptr<EH> eventHandler;
        
//        using ViewBase::ViewBase;
        
        std::function<void(const std::string&)> errorHappened;
        
        virtual void init(){}
        
        /*virtual void willAppear() override{
            this->eventHandler->viewWillAppear();
        }*/
        
        /*virtual void didAppear() override{
            this->eventHandler->viewDidAppear();
        }*/
        
        /*virtual void willDisappear() override{
            this->eventHandler->viewWillDisappear();
        }*/
        
        /*template<class T>
        void setEventHandler(std::shared_ptr<T> ptr){
            this->eventHandler=std::dynamic_pointer_cast<EH>(ptr);
        }*/
        
        virtual void dispose() override{
            this->Disposable::dispose();
//            this->eventHandler=nullptr;
        }
    protected:
//        typedef View<EH,UI> V;
    };
}

#endif /* View_h */
