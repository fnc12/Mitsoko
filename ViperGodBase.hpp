//
//  ViperGodBase.hpp
//  Jako
//
//  Created by John Zakharov on 27.04.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef ViperGodBase_h
#define ViperGodBase_h

#include <string>
#include <tuple>
#include <type_traits>
#include <memory>
#include <map>
#include <cstring>
#include <vector>
#include "Disposable.hpp"
#include "View.hpp"
#include "Dispatch.hpp"
#include "Module.hpp"

namespace Viper{
    struct ViperGodBase{
        typedef long ViewId;
        
        template<typename H,typename... Tail>
        struct TupleCutter;
        
        template<typename H,typename... Tail>
        struct TupleCutter<std::tuple<H,Tail...>>{
            typedef H Head_t;
            typedef std::tuple<Tail...> Tail_t;
        };
        
        void viewWillAppear(ViewId viewId){
            auto it=this->viewPool.find(viewId);
            if(it!=this->viewPool.end()){
                it->second->willAppear();
            }
        }
        
        void viewDidAppear(ViewId viewId){
            auto it=this->viewPool.find(viewId);
            if(it!=this->viewPool.end()){
                it->second->didAppear();
            }
        }
        
        void viewWillDisappear(ViewId viewId){
            auto it=this->viewPool.find(viewId);
            if(it!=this->viewPool.end()){
                it->second->willDisappear();
            }
        }
        
        const void* destroyView(ViewId viewId){
            const void *res=nullptr;
            const auto it=this->viewPool.find(viewId);
            if(it!=this->viewPool.end()){
                res=it->second->handle;
                this->viewPool.erase(it);
            }
            const auto it2=this->disposables.find(viewId);
            if(it2!=this->disposables.end()){
                for(const auto &disposablePointer:it2->second){
                    disposablePointer->dispose();
                }
                it2->second.clear();
                this->disposables.erase(it2);
            }
            return res;
        }
        
        void sendMessageToView(ViewId viewId,int messageCode,std::string argumentsString=""){
            const auto it=this->viewPool.find(viewId);
            if(it!=this->viewPool.end()){
                it->second->messageReceived(messageCode,std::move(argumentsString));
            }else{
                cout<<"view not found with id "<<viewId<<endl;
            }
        }
        
#ifdef __ANDROID__
        void onActivityResult(ViewId viewId,int requestCode,int resultCode,jobject data){
            const auto it=this->viewPool.find(viewId);
            if(it!=this->viewPool.end()){
                it->second->onActivityResult(requestCode,resultCode,data);
            }else{
                cout<<"view not found with id "<<viewId<<endl;
            }
        }
        
#endif
        
//    protected:
        std::map<ViewId, std::shared_ptr<ViewBase>> viewPool;
        std::map<ViewId, std::vector<std::shared_ptr<Disposable>>> disposables;
        ViewId nextViewId=0;
    };
}

#endif /* ViperGodBase_h */
