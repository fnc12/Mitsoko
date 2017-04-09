//
//  ViperGod.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "ViperGod.hpp"

Mitsoko::God Mitsoko::God::shared;

using std::cout;
using std::endl;

using Mitsoko::PresenterBase;

Mitsoko::God::ViewId Mitsoko::God::createView(const std::string &viewName,const void *handle){
    std::vector<std::shared_ptr<Disposable>> disposablesVector;
    auto presenterPointer = this->_createView<R::ModulesTuple>(viewName,handle,disposablesVector);
    if(presenterPointer){
        const auto viewId = this->nextViewId++;
//        cout << "presenterPointer[" << viewId << "] = " << presenterPointer << ", handle = " << handle << endl;
//        this->viewPool.insert({viewId,viewPointer});
        this->presenters.insert({viewId, presenterPointer});
        this->disposables.insert({viewId,std::move(disposablesVector)});
        return viewId;
    }else{
        return -1;
    }
}

template<>
std::shared_ptr<PresenterBase> Mitsoko::God::_createView<std::tuple<>>(const std::string &viewName,
                                                                       const void *handle,
                                                                       std::vector<std::shared_ptr<Disposable>> &disposables)
{
    return nullptr;
}

void Mitsoko::God::viewWillAppear(ViewId viewId){
    auto it=this->presenters.find(viewId);
    if(it != this->presenters.end()){
        auto presenterPointer = it->second;
        auto viewBasePointer = presenterPointer->getViewBase();
        if(viewBasePointer->willAppear){
            viewBasePointer->willAppear();
        }
        /*if(it->second->willAppear){
            it->second->willAppear();
        }*/
    }
}

void Mitsoko::God::viewDidAppear(ViewId viewId){
    auto it=this->presenters.find(viewId);
    if(it != this->presenters.end()){
//        auto viewBasePointer = it->second;
        auto presenterPointer = it->second;
        auto viewBasePointer = presenterPointer->getViewBase();
        if(viewBasePointer->didAppear){
            viewBasePointer->didAppear();
        }
    }
}

void Mitsoko::God::viewWillDisappear(ViewId viewId){
    auto it=this->presenters.find(viewId);
    if(it != this->presenters.end()){
//        auto viewBasePointer = it->second;
        auto presenterPointer = it->second;
        auto viewBasePointer = presenterPointer->getViewBase();
        if(viewBasePointer->willDisappear){
            viewBasePointer->willDisappear();
        }
    }
}

const void* Mitsoko::God::destroyView(ViewId viewId){
    const void *res = nullptr;
    const auto it = this->presenters.find(viewId);
    if(it != this->presenters.end()){
//        res = it->second->handle;
        res = it->second->getViewBase()->handle;
        this->presenters.erase(it);
    }
    const auto it2 = this->disposables.find(viewId);
    if(it2 != this->disposables.end()){
        for(const auto &disposablePointer:it2->second){
            disposablePointer->dispose();
        }
        it2->second.clear();
        this->disposables.erase(it2);
    }
    return res;
}

void Mitsoko::God::sendMessageToView(ViewId viewId,int messageCode,std::string argumentsString){
    const auto it = this->presenters.find(viewId);
    if(it != this->presenters.end()){
        if(it->second->getViewBase()->messageReceived){
            it->second->getViewBase()->messageReceived(messageCode, std::move(argumentsString));
        }
    }else{
        cout<<"view not found with id "<<viewId<<endl;
    }
}

#ifdef __ANDROID__
void Mitsoko::God::onActivityResult(ViewId viewId,int requestCode,int resultCode,jobject data){
    const auto it=this->presenters.find(viewId);
    if(it != this->presenters.end()){
        it->second->getViewBase()->onActivityResult(requestCode,resultCode,data);
    }else{
        cout<<"view not found with id "<<viewId<<endl;
    }
}
#endif
