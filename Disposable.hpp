//
//  Disposable.hpp
//  Jako
//
//  Created by John Zakharov on 20.03.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef Disposable_h
#define Disposable_h

#include <mutex>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Viper{
    using std::cout;
    using std::endl;
    
    struct Disposable{
        typedef unsigned Id;
        
        const Id id;
        
        struct Observer{
            virtual void disposableDidDispose(Id id)=0;
            
            virtual ~Observer(){
                Disposable::unsubscribe(this);
            }
        };
        
        Disposable():id(generateId()){}
        
        virtual void dispose(){
            for(auto observer:observers()){
                const auto id=this->id;
                observer->disposableDidDispose(id);
            }
        }
        
        static void subscribe(Observer *observer){
            observersMutex().lock();
            observers().emplace_back(observer);
            observersMutex().unlock();
        }
        
        static void unsubscribe(Observer *observer){
            observersMutex().lock();
            const auto it=std::find(observers().begin(), observers().end(), observer);
            if(observers().end()!=it){
                observers().erase(it);
            }
            observersMutex().unlock();
        }
        
    protected:
        
        static std::mutex& observersMutex(){
            static std::mutex res;
            return res;
        }
        
        static std::vector<Observer*>& observers(){
            static std::vector<Observer*> res;
            return res;
        }
        
        static Id generateId(){
            static Id previousId=0;
            static std::mutex idLock;
            idLock.lock();
            const auto res=previousId++;
            idLock.unlock();
            return res;
        }
    };
}

#endif /* Disposable_h */
