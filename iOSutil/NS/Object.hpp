
#pragma once

#ifdef __APPLE__
#include <objc/message.h>
#include <UIKit/UIKit.h>
#endif

#include <string>
#include <type_traits>
#include <cassert>
#include <cstddef>
#include <ostream>

namespace NS {
#ifdef __APPLE__
    inline Class getClass(const std::string &className){
        return objc_getClass(className.c_str());
    }
#endif
    
    struct Object{
        typedef const void *Handle;
        Handle handle;
        
        /**
         *  Empty constructor. Equals nil reference.
         */
        Object():Object(nullptr){}
        
        /**
         *  Strong reference creation constructor.
         */
        Object(decltype(handle)handle_):
        handle(handle_){
#ifdef __APPLE__
            if(this->handle){
                this->retain();
            }
#endif
        }
        
        /**
         *  Copy strong reference on init.
         */
        Object(const Object &other):
        handle(other.handle){
#ifdef __APPLE__
            if(this->handle){
                this->retain();
            }
#endif
        }
        
        /**
         *  Copy strong reference on assign.
         */
        Object& operator=(const Object &other){
            this->cleanUp();
            this->handle=other.handle;
#ifdef __APPLE__
            if(this->handle){
                this->retain();
            }
#endif
            return *this;
        }
        
        /**
         *  Move constructor. Has not retain/release.
         */
        Object(Object &&object):handle(object.handle)/*,shouldClearOnDestroy(object.shouldClearOnDestroy)*/{
            object.handle=nullptr;
//            object.shouldClearOnDestroy=false;
        }
        
        /**
         *  Move assignment. Also hasn't retain/release.
         */
        Object& operator=(Object &&object){
            this->cleanUp();
            this->handle=object.handle;
//            this->shouldClearOnDestroy=object.shouldClearOnDestroy;
            object.handle=nullptr;
//            object.shouldClearOnDestroy=false;
            return *this;
        }
        
        virtual ~Object(){
            this->cleanUp();
        }
        
#ifdef __APPLE__
        std::string description(){
            NS::Object s=this->sendMessage<Handle>("description");
            return s.sendMessage<const char*>("UTF8String");
        }
        
        template<class T>
        bool isKindOfClass(){
            if(auto cls=NS::getClass(T::className())){
                return this->sendMessage<BOOL>("isKindOfClass:", cls);
            }else{
                return false;
            }
        }
        
        template<class T>
        bool isMemberOfClass(){
            if(auto cls=NS::getClass(T::className())){
                return this->sendMessage<BOOL>("isMemberOfClass:", cls);
            }else{
                return false;
            }
        }
        
        /**
         *  Operator is from swift.
         */
        template<class T>
        bool is(){
            return this->isKindOfClass<T>();
        }
        
        /**
         *  Operator as from swift. Acts like as? version.
         */
        template<class T>
        T as(){
            if(this->is<T>()){
                return T(this->handle);
            }else{
                return {};
            }
        }
        
        template<class RT,class ...Args>
        RT sendMessage(const std::string &message,const Args& ...args){
            return sendMessage<RT>(this->handle, message, args...);
        }

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
//                res.shouldClearOnDestroy=true;
                return std::move(res);
            }else{
                return nullptr;
            }
        }
        
        template<class T>
        static T create(){
            const auto &className=T::className();
            return std::move(create<T>(className));
        }
#endif
    protected:
//        bool shouldClearOnDestroy=false;
#ifdef __APPLE__
        
        /**
         *  This functions must not be called explictly. They called automtacally
         *  in object`s constructor and destructor with ARC-like style.
         */
        void retain(){
            CFRetain(CFTypeRef(this->handle));
        }
        
        void release(){
            CFRelease(CFTypeRef(this->handle));
        }
        
    public:
        int retainCount(){
            return int(CFGetRetainCount(CFTypeRef(this->handle)));
        }
#endif
    private:
        void cleanUp(){
#ifdef __APPLE__
            if(this->handle){
                this->release();
                this->handle=nullptr;
            }
#endif
        }
    };
#ifdef __APPLE__
    inline std::ostream& operator<<(std::ostream &os,NS::Object &obj){
        os<<obj.description()<<endl;
        return os;
    }
#endif
}
