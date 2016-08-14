
#ifndef __VIPER__IOS_UTIL__UI__BAR_BUTTON_ITEM__
#define __VIPER__IOS_UTIL__UI__BAR_BUTTON_ITEM__

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/Disposable.hpp"
#include "Image.hpp"
#include "BarItem.hpp"
#include <functional>
#include <map>

namespace UI {
    
    struct BarButtonItem:public UI::BarItem{
        
        using BarItem::BarItem;
        
#ifdef __APPLE__
        
        static const std::string className;
        
//        STATIC_VAR(const std::string, className, "UIBarButtonItem");
        
        typedef std::function<void(UI::BarButtonItem)> Touched;
        
        enum class Style{
            Plain=UIBarButtonItemStylePlain,
            Bordered=UIBarButtonItemStyleBordered,
            Done=UIBarButtonItemStyleDone,
        };
        
        static UI::BarButtonItem create(const UI::Image &image,Style style,Touched f,const Viper::Disposable *disposable);
        
        static UI::BarButtonItem create(const std::string &title,Style style,Touched f,const Viper::Disposable *disposable);
        
        static void touched(Handle handle);
        
    protected:
        
        typedef std::map<Handle, Touched> TouchedMap;
        static TouchedMap touchedMap;
//        STATIC_VAR(TouchedMap, touchedMap, {});
        
        typedef std::map<Viper::Disposable::Id, Handle> DisposablesMap;
        static DisposablesMap disposablesMap;
//        STATIC_VAR(DisposablesMap, disposablesMap, {});
        
        struct Observer:public Viper::Disposable::Observer{
            
            virtual void disposableDidDispose(Viper::Disposable::Id id) override;
        };
        
        static Observer observer;
//        STATIC_VAR(Observer, observer, {});
        
        Handle initWithImage(const UI::Image &image,Style style,const NS::Object &target,SEL action);
        
        Handle initWithTitle(const CF::String &title,Style style,const NS::Object &target,SEL action);
        
#endif  //__APPLE__
        
    };
}

#endif  //__VIPER__IOS_UTIL__UI__BAR_BUTTON_ITEM__
