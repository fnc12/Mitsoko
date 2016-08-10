//
//  Disposable.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Disposable.hpp"

std::mutex Viper::Disposable::observersMutex;

std::vector<Viper::Disposable::Observer*> Viper::Disposable::observers;

Viper::Disposable::Observer::~Observer(){
    Disposable::unsubscribe(this);
}

Viper::Disposable::Disposable():id(generateId()){}

void Viper::Disposable::dispose(){
    for(auto observer:observers){
        const auto id=this->id;
        observer->disposableDidDispose(id);
    }
}

void Viper::Disposable::subscribe(Observer *observer){
    observersMutex.lock();
    observers.emplace_back(observer);
    observersMutex.unlock();
}

void Viper::Disposable::unsubscribe(Observer *observer){
    observersMutex.lock();
    const auto it=std::find(observers.begin(),
                            observers.end(),
                            observer);
    if(observers.end() != it){
        observers.erase(it);
    }
    observersMutex.unlock();
}

Viper::Disposable::Id Viper::Disposable::generateId(){
    static Id previousId=0;
    static std::mutex idLock;
    idLock.lock();
    const auto res=previousId++;
    idLock.unlock();
    return res;
}
