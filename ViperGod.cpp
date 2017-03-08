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

using Viper::PresenterBase;

Viper::God::ViewId Viper::God::createView(const std::string &viewName,const void *handle){
    std::vector<std::shared_ptr<Disposable>> disposablesVector;
    auto presenterPointer = this->_createView<R::ModulesTuple>(viewName,handle,disposablesVector);
    if(presenterPointer){
        const auto viewId = this->nextViewId++;
        cout << "presenterPointer[" << viewId << "] = " << presenterPointer << ", handle = " << handle << endl;
//        this->viewPool.insert({viewId,viewPointer});
        this->presenters.insert({viewId, presenterPointer});
        this->disposables.insert({viewId,std::move(disposablesVector)});
        return viewId;
    }else{
        return -1;
    }
}

template<>
std::shared_ptr<PresenterBase> Viper::God::_createView<std::tuple<>>(const std::string &viewName,
                                                                       const void *handle,
                                                                       std::vector<std::shared_ptr<Disposable>> &disposables)
{
    return nullptr;
}

void Viper::God::viewWillAppear(ViewId viewId){
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

void Viper::God::viewDidAppear(ViewId viewId){
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

void Viper::God::viewWillDisappear(ViewId viewId){
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

const void* Viper::God::destroyView(ViewId viewId){
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

void Viper::God::sendMessageToView(ViewId viewId,int messageCode,std::string argumentsString){
//    cout << "argumentsString = " << argumentsString << endl;
#ifdef __ANDROID__
    LOGI("%s", argumentsString.c_str());
#endif  //  __ANDROID__
    const auto it=this->presenters.find(viewId);
    if(it != this->presenters.end()){
        it->second->getViewBase()->messageReceived(messageCode, std::move(argumentsString));
//        it->second->messageReceived(messageCode,std::move(argumentsString));
    }else{
        cout<<"view not found with id "<<viewId<<endl;
    }
}

#ifdef __ANDROID__
void Viper::God::onActivityResult(ViewId viewId,int requestCode,int resultCode,jobject data){
    const auto it=this->presenters.find(viewId);
    if(it != this->presenters.end()){
        it->second->getViewBase()->onActivityResult(requestCode,resultCode,data);
    }else{
        cout<<"view not found with id "<<viewId<<endl;
    }
}
#endif
