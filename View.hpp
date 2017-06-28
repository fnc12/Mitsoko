//
//  View.hpp
//  Jako
//
//  Created by John Zakharov on 19.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef __VIPER_VIEW_H
#define __VIPER_VIEW_H

#include <memory>
#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include <functional>

#include "Disposable.hpp"
//#include "ViewPresenterIF.hpp"
#include "ImageCache.hpp"
#include "Language.hpp"
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

//#define VIEW_DECL(module) struct View:public Viper::View<module::EventHandler, module::UserInterface>,Selfish<View>

/**
 *  Used fo simplifying client member references declaration.
 */
#ifdef __APPLE__
#define FIELD_DECL(type,name) type name(){return NS::Object::sendMessage<Handle>(this->handle,#name);}
#else
#define FIELD_DECL(type,name) type name(){return java::lang::Object(this->handle).getField<type>(#name);}
#endif

namespace Mitsoko{
    
    struct ViewBase{
        
        const void *handle = nullptr;
        
        virtual ~ViewBase();
        
        std::function<void()> willAppear;
        std::function<void()> didAppear;
        std::function<void()> willDisappear;
        std::function<void(int, std::string)> messageReceived;
        
//        virtual void messageReceived(int messageCode, std::string args) {};
        
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
    struct View : public ViewBase, public Mitsoko::Disposable {
        
        std::function<void(const std::string&)> errorHappened;
        
        virtual void init(){}
        
        virtual void dispose() override{
            this->Mitsoko::Disposable::dispose();
        }
    };
}

#endif /* __VIPER_VIEW_H */
