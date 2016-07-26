
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/Disposable.hpp"
#include "Image.hpp"
#include <functional>
#include <map>

namespace UI {
    struct BarButtonItem:public UI::BarItem{
        using BarItem::BarItem;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIBarButtonItem");
        
        typedef std::function<void(UI::BarButtonItem)> Touched;
        
        enum class Style{
            Plain=UIBarButtonItemStylePlain,
            Bordered=UIBarButtonItemStyleBordered,
            Done=UIBarButtonItemStyleDone,
        };
        
        static UI::BarButtonItem create(const UI::Image &image,Style style,Touched f,const Viper::Disposable *disposable){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "alloc");
            BarButtonItem res(handle);
            NS::Object target;
            SEL action=nil;
            if(f && disposable){
                cls=NS::getClass("UIBarButtonItemEventHandler");
                assert(cls);
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(cls, "shared");
                assert(sharedEventHandler);
                target=sharedEventHandler;
                action=sel_getUid("barButtonItemTouched:");
                assert(action);
                touchedMap().insert({res.handle, f});
                disposablesMap().insert({disposable->id, res.handle});
                Viper::Disposable::subscribe(&observer());
            }
            res.initWithImage(image, style, target, action);
            return std::move(res);
        }
        
        static UI::BarButtonItem create(const std::string &title,Style style,Touched f,const Viper::Disposable *disposable){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "alloc");
            BarButtonItem res(handle);
            auto t=CF::String::create(title);
            NS::Object target;
            SEL action=nil;
            if(f && disposable){
                cls=NS::getClass("UIBarButtonItemEventHandler");
                assert(cls);
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(cls, "shared");
                assert(sharedEventHandler);
                target=sharedEventHandler;
                action=sel_getUid("barButtonItemTouched:");
                assert(action);
                touchedMap().insert({res.handle, f});
                disposablesMap().insert({disposable->id, res.handle});
                Viper::Disposable::subscribe(&observer());
            }
            res.initWithTitle(t, style, target, action);
            return std::move(res);
        }
        
        static void touched(Handle handle){
            auto it=touchedMap().find(handle);
            if(it != touchedMap().end()){
                it->second(handle);
            }else{
                std::cerr<<"touched callback not found for UI::BarButtonItem for handle "<<handle<<endl;
            }
        }
        
    protected:
        
        typedef std::map<Handle, Touched> TouchedMap;
        STATIC_VAR(TouchedMap, touchedMap, {});
        
        typedef std::map<Viper::Disposable::Id, Handle> DisposablesMap;
        STATIC_VAR(DisposablesMap, disposablesMap, {});
        
        struct Observer:public Viper::Disposable::Observer{
            virtual void disposableDidDispose(Viper::Disposable::Id id) override{
                auto it=disposablesMap().find(id);
                if(it != disposablesMap().end()){
                    auto handle=it->second;
                    disposablesMap().erase(it);
                    auto it2=touchedMap().find(handle);
                    if(it2 != touchedMap().end()){
                        touchedMap().erase(it2);
                    }
                    Viper::Disposable::unsubscribe(&observer());
                }
            }
        };
        
        STATIC_VAR(Observer, observer, {});
        
        Handle initWithImage(const UI::Image &image,Style style,const NS::Object &target,SEL action){
            return this->sendMessage<Handle>("initWithImage:style:target:action:",
                                             image.handle,
                                             UIBarButtonItemStyle(style),
                                             target.handle,
                                             action);
        }
        
        Handle initWithTitle(const CF::String &title,Style style,const NS::Object &target,SEL action){
            return this->sendMessage<Handle>("initWithTitle:style:target:action:",
                                             title.handle,
                                             UIBarButtonItemStyle(style),
                                             target.handle,
                                             action);
        }
#endif
    };
}
