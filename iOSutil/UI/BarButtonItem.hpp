
#pragma once

#include "Viper/iOSutil/NS/Object.hpp"

namespace UI {
    struct BarButtonItem:public UI::BarItem{
        using BarItem::BarItem;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIBarButtonItem");
        
        enum class Style{
            Plain=UIBarButtonItemStylePlain,
            Bordered=UIBarButtonItemStyleBordered,
            Done=UIBarButtonItemStyleDone,
        };
        
        static UI::BarButtonItem create(const std::string &title,Style style){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "alloc");
            BarButtonItem res(handle);
            res.shouldClearOnDestroy=true;
            auto t=CF::String::create(title);
            res.initWithTitle(t, style);
            return std::move(res);
        }
        
    protected:
        
        Handle initWithTitle(const CF::String &title,Style style){
            return this->sendMessage<Handle>("initWithTitle:style:target:action:",
                                             title.handle,
                                             UIBarButtonItemStyle(style),
                                             nil,
                                             nil);
        }
#endif
    };
}
