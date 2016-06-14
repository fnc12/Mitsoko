
#pragma once

#ifdef __APPLE__
#include <objc/message.h>
#include <UIKit/UIKit.h>
#endif

#include <string>
#include <type_traits>
#include <cassert>
#include <cstddef>

namespace NS {
#ifdef __APPLE__
    inline Class getClass(const std::string &className){
        return objc_getClass(className.c_str());
    }
#endif
    
    struct Object{
        typedef const void *Handle;
        Handle handle;
        
        Object():Object(nullptr){}
        Object(decltype(handle)handle_):handle(handle_){}
        Object(const Object&)=default;
        Object & operator=(const Object &)=default;
        
        Object(Object &&object):handle(object.handle),shouldClearOnDestroy(object.shouldClearOnDestroy){
            object.handle=nullptr;
            object.shouldClearOnDestroy=false;
        }
        
        Object& operator=(Object &&object){
            this->cleanUp();
            this->handle=object.handle;
            this->shouldClearOnDestroy=object.shouldClearOnDestroy;
            object.handle=nullptr;
            object.shouldClearOnDestroy=false;
            return *this;
        }
        
        virtual ~Object(){
            this->cleanUp();
        }
        
        template<class RT,class ...Args>
        RT sendMessage(const std::string &message,const Args& ...args){
            return sendMessage<RT>(this->handle, message, args...);
        }
#ifdef __APPLE__
        Class getClass(){
            return this->sendMessage<Class>("class");
        }
#endif
        operator bool()const{
            return this->handle != nullptr;
        }
        
        operator Handle()const{
            return this->handle;
        }
        
        template<class RT,class R,class ...Args>
        static RT sendMessage(const R &receiver,const std::string &message,const Args& ...args){
#ifdef __APPLE__
            return reinterpret_cast<RT(*)(R,SEL,Args...)>(objc_msgSend)(receiver,sel_getUid(message.c_str()),args...);
#else
            return {};
#endif
        }
#ifdef __APPLE__
        template<class T>
        static T create(const std::string &className){
            static_assert(std::is_base_of<Object, T>::value,"T must derive NS::Object");
            auto cls=NS::getClass(className);
            if(cls){
                T res=sendMessage<Handle>(cls, "alloc");
                res.template sendMessage<Handle>("init");
                res.shouldClearOnDestroy=true;
                return std::move(res);
            }else{
                return nullptr;
            }
        }
#endif
    protected:
        bool shouldClearOnDestroy=false;
    private:
        void cleanUp(){
#ifdef __APPLE__
            if(this->shouldClearOnDestroy){
                CFRelease(CFTypeRef(this->handle));
                this->shouldClearOnDestroy=false;
            }
#endif
        }
    };
}
