//
//  ViperGod.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ViperGod.hpp"

Viper::God Viper::God::shared;

using std::cout;
using std::endl;

Viper::God::ViewId Viper::God::createView(const std::string &viewName,const void *handle){
    std::vector<std::shared_ptr<Disposable>> disposablesVector;
    auto viewPointer=this->_createView<R::ModulesTuple>(viewName,handle,disposablesVector);
    if(viewPointer){
        const auto viewId=this->nextViewId++;
        this->viewPool.insert({viewId,viewPointer});
        this->disposables.insert({viewId,std::move(disposablesVector)});
        return viewId;
    }else{
        return -1;
    }
}

template<>
std::shared_ptr<Viper::ViewBase> Viper::God::_createView<std::tuple<>>(const std::string &viewName,
                                                                       const void *handle,
                                                                       std::vector<std::shared_ptr<Disposable>> &disposables)
{
    return {};
}

void Viper::God::viewWillAppear(ViewId viewId){
    auto it=this->viewPool.find(viewId);
    if(it != this->viewPool.end()){
        it->second->willAppear();
    }
}

void Viper::God::viewDidAppear(ViewId viewId){
    auto it=this->viewPool.find(viewId);
    if(it != this->viewPool.end()){
        it->second->didAppear();
    }
}

void Viper::God::viewWillDisappear(ViewId viewId){
    auto it=this->viewPool.find(viewId);
    if(it != this->viewPool.end()){
        it->second->willDisappear();
    }
}

const void* Viper::God::destroyView(ViewId viewId){
    const void *res=nullptr;
    const auto it=this->viewPool.find(viewId);
    if(it != this->viewPool.end()){
        res=it->second->handle;
        this->viewPool.erase(it);
    }
    const auto it2=this->disposables.find(viewId);
    if(it2 != this->disposables.end()){
        for(const auto &disposablePointer:it2->second){
            disposablePointer->dispose();
        }
        it2->second.clear();
        this->disposables.erase(it2);
    }
    return res;
}

void Viper::God::sendMessageToView(ViewId viewId,int messageCode,std::string argumentsString){
    const auto it=this->viewPool.find(viewId);
    if(it != this->viewPool.end()){
        it->second->messageReceived(messageCode,std::move(argumentsString));
    }else{
        cout<<"view not found with id "<<viewId<<endl;
    }
}

#ifdef __ANDROID__
void Viper::God::onActivityResult(ViewId viewId,int requestCode,int resultCode,jobject data){
    const auto it=this->viewPool.find(viewId);
    if(it != this->viewPool.end()){
        it->second->onActivityResult(requestCode,resultCode,data);
    }else{
        cout<<"view not found with id "<<viewId<<endl;
    }
}
#endif
