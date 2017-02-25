
#ifndef __VIPER__IOS_UTIL__UI__BAR_BUTTON_ITEM__
#define __VIPER__IOS_UTIL__UI__BAR_BUTTON_ITEM__

#include "Viper/iOSutil/NS/Object.hpp"
#include "Viper/Disposable.hpp"
#include "Image.hpp"
#include "BarItem.hpp"
#include <functional>
#include <map>

namespace UI {
    
    struct BarButtonItem : public UI::BarItem {
        
        using BarItem::BarItem;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        typedef std::function<void(UI::BarButtonItem)> Touched;
        
        enum class Style{
            Plain = UIBarButtonItemStylePlain,
#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_8_0
            Bordered = UIBarButtonItemStyleBordered,
#endif
            Done = UIBarButtonItemStyleDone,
        };
        
        static UI::BarButtonItem create(const UI::Image &image,
                                        Style style,
                                        Touched f,
                                        const Viper::Disposable *disposable);
        
        static UI::BarButtonItem create(const std::string &title,
                                        Style style,
                                        Touched f,
                                        const Viper::Disposable *disposable);
        
        static void touched(Handle handle);
        
    protected:
        
        typedef std::map<Handle, Touched> TouchedMap;
        static TouchedMap touchedMap;
        
        typedef std::map<Viper::Disposable::Id, Handle> DisposablesMap;
        static DisposablesMap disposablesMap;
        
        struct Observer : public Viper::Disposable::Observer {
            
            virtual void disposableDidDispose(Viper::Disposable::Id id) override;
        };
        
        static Observer observer;
        
        Handle initWithImage(const UI::Image &image,Style style,const NS::Object &target,SEL action);
        
        Handle initWithTitle(const CF::String &title,Style style,const NS::Object &target,SEL action);
        
#endif  //__APPLE__
        
    };
}

#endif  //__VIPER__IOS_UTIL__UI__BAR_BUTTON_ITEM__
