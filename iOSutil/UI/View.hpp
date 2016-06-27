
#pragma once

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
        
        void setBackgroundColor(const UI::Color &newValue){
            this->sendMessage<void>("setBackgroundColor:", newValue.handle);
        }
        
        UI::Color backgroundColor(){
            return this->sendMessage<Handle>("backgroundColor");
        }
        
        CG::Rect frame(){
            return this->sendMessage<CG::Rect>("frame");
        }
        
        void setContentMode(ContentMode newValue){
            this->sendMessage<void>("setContentMode:", UIViewContentMode(newValue));
        }
        
        ContentMode contentMode(){
            return ContentMode(this->sendMessage<UIViewContentMode>("contentMode"));
        }
        
        void setHidden(bool newValue){
            this->sendMessage<void>("setHidden:", newValue);
        }
        
        void setTransform(const CG::AffineTransform &newValue){
            this->sendMessage<void>("setTransform:", newValue);
        }
        
        CG::AffineTransform transform(){
            return this->sendMessage<CG::AffineTransform>("transform");
        }
#endif
    };
}
