
#ifndef __VIPER__IOS_UTIL__UI__VIEW__
#define __VIPER__IOS_UTIL__UI__VIEW__

#include "Responder.hpp"
#include "Viper/iOSutil/CG/AffineTransform.hpp"
#include "Viper/iOSutil/CG/Rect.hpp"
#include "Color.hpp"

namespace UI {
    struct View:public UI::Responder{
        using Responder::Responder;
#ifdef __APPLE__
        enum class ContentMode{
            ScaleToFill = UIViewContentModeScaleToFill,
            ScaleAspectFit = UIViewContentModeScaleAspectFit,
            ScaleAspectFill = UIViewContentModeScaleAspectFill,
            Redraw = UIViewContentModeRedraw,
            Center = UIViewContentModeCenter,
            Top = UIViewContentModeTop,
            Bottom = UIViewContentModeBottom,
            Left = UIViewContentModeLeft,
            Right = UIViewContentModeRight,
            TopLeft = UIViewContentModeTopLeft,
            TopRight = UIViewContentModeTopRight,
            BottomLeft = UIViewContentModeBottomLeft,
            BottomRight = UIViewContentModeBottomRight,
        };
        
        void addSubview(const UI::View &view);
        
        void setBackgroundColor(const UI::Color &newValue);
        
        UI::Color backgroundColor();
        
        void setFrame(const CG::Rect &newValue);
        
        CG::Rect frame(){
            return this->sendMessage<CG::Rect>("frame");
        }
        
        void setContentMode(ContentMode newValue);
        
        ContentMode contentMode();
        
        void setHidden(bool newValue);
        
        void setTransform(const CG::AffineTransform &newValue);
        
        CG::AffineTransform transform();
#endif
    };
}

#endif  //__VIPER__IOS_UTIL__UI__VIEW__
