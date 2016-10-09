
#ifndef __VIPER__IOS_UTIL__NS__OBJECT__
#define __VIPER__IOS_UTIL__NS__OBJECT__

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
    Class getClass(const std::string &className);
#endif
    
    struct Object{
        typedef const void *Handle;
        Handle handle;
        
#ifdef __APPLE__
        static const std::string className;
        
        /**
         *  Empty constructor. Equals nil reference.
         */
        Object();
        
        /**
         *  Strong reference creation constructor.
         */
        Object(decltype(handle)handle_);
        
        /**
         *  Copy strong reference on init.
         */
        Object(const Object &other):
        handle(other.handle){
            if(this->handle){
                this->retain();
            }
        }
        
        /**
         *  Copy strong reference on assign.
         */
        Object& operator=(const Object &other);
        
        /**
         *  Move constructor. Has not retain/release.
         */
        Object(Object &&object);
        
        /**
         *  Move assignment. Also hasn't retain/release.
         */
        Object& operator=(Object &&object);
        
        virtual ~Object();
//#endif
//#ifdef __APPLE__
        std::string description();
        
        template<class T>
        bool isKindOfClass(){
            if(auto cls=NS::getClass(T::className)){
                return this->sendMessage<BOOL>("isKindOfClass:", cls);
            }else{
                return false;
            }
        }
        
        template<class T>
        bool isMemberOfClass(){
            if(auto cls=NS::getClass(T::className)){
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

        Class getClass();
        
        operator bool() const;
        
        operator Handle() const;
//#endif
        template<class RT,class R,class ...Args>
        static RT sendMessage(const R &receiver,const std::string &message,const Args& ...args){
//#ifdef __APPLE__
            auto sel=sel_getUid(message.c_str());
            return reinterpret_cast<RT(*)(R,SEL,Args...)>(objc_msgSend)(receiver,sel,args...);
//#else
//            return {};
        }
//#endif
//#ifdef __APPLE__
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
            const auto &className=T::className;
            return std::move(create<T>(className));
        }
//#endif
    protected:
//        bool shouldClearOnDestroy=false;
//#ifdef __APPLE__
        
        /**
         *  This functions must not be called explictly. They called automtacally
         *  in object`s constructor and destructor with ARC-like style.
         */
        void retain();
        
        void release();
        
    public:
        int retainCount();
//#endif
    private:
        void cleanUp();
#endif
    };
//#endif
//#ifdef __APPLE__
    std::ostream& operator<<(std::ostream &os,NS::Object &obj);
}

#endif  //__VIPER__IOS_UTIL__NS__OBJECT__
