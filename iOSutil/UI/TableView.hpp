
#pragma once

#include "ScrollView.hpp"
#include "Viper/TableListAdapter.hpp"
#include "ImageView.hpp"

namespace UI {
    struct TableView:public UI::ScrollView{
        using ScrollView::ScrollView;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UITableView");
        
        enum class RowAnimation{
            Fade = UITableViewRowAnimationFade,
            Right = UITableViewRowAnimationRight,
            Left = UITableViewRowAnimationLeft,
            Top = UITableViewRowAnimationTop,
            Bottom = UITableViewRowAnimationBottom,
            None = UITableViewRowAnimationNone,
            Middle = UITableViewRowAnimationMiddle,
            Automatic = UITableViewRowAnimationAutomatic,
        };
        
        void reloadSections(const NS::IndexSet &indexSet,RowAnimation animation){
            auto is=indexSet.handle;
            this->sendMessage<void>("reloadSections:withRowAnimation:", is,UITableViewRowAnimation(animation));
        }
        
        void reloadData(){
            this->sendMessage<void>(this->handle, "reloadData");
        }
        
        void beginUpdates(){
            this->sendMessage<void>(this->handle, "beginUpdates");
        }
        
        /**
         *  This function doesn't exist in UIKit. This is a special function 
         *  for settings a crossplatform adapter. This function also exists for
         *  android::widget::ListView with two arguments where second argument is
         *  android::content::Context.
         */
        template<class T>
        Viper::TableListAdapter::AdapterId setAdapter(T ad){
            auto pointer=std::make_shared<T>(std::move(ad));
            auto adapterPointer=std::dynamic_pointer_cast<Viper::AdapterBase>(pointer);
            auto adapterId=Viper::TableListAdapter::registerAdapter(this->handle, adapterPointer);
            auto sharedAdapterClass=NS::getClass("ViperTableViewAdapter");
            auto sharedAdapter=NS::Object::sendMessage<Handle>(sharedAdapterClass,"shared");
            this->sendMessage<void>("setDataSource:", sharedAdapter);
            this->sendMessage<void>("setDelegate:", sharedAdapter);
            return adapterId;
        }
        
        struct Cell:public UI::View{
            using View::View;
            STATIC_VAR(std::string, className, "UITableViewCell");
            
            enum class AccessoryType{
                None=UITableViewCellAccessoryNone,
                DisclosureIndicator=UITableViewCellAccessoryDisclosureIndicator,
                DetailDisclosureButton=UITableViewCellAccessoryDetailDisclosureButton,
                Checkmark=UITableViewCellAccessoryCheckmark,
                DetailButton=UITableViewCellAccessoryDetailButton,
            };
            
            UI::ImageView imageView(){
                return this->sendMessage<Handle>("imageView");
            }
            
            UI::Label detailTextLabel(){
                return this->sendMessage<Handle>("detailTextLabel");
            }
            
            UI::Label textLabel(){
                return this->sendMessage<Handle>("textLabel");
            }
            
            void setAccessoryType(AccessoryType newValue){
                this->sendMessage<void>("setAccessoryType:", UITableViewCellAccessoryType(newValue));
            }
            
            AccessoryType accessoryType(){
                return AccessoryType(this->sendMessage<UITableViewCellAccessoryType>("accessoryType"));
            }
        };
#endif
    };
}
