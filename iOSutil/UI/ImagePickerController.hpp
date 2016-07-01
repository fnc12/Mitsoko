
#pragma once

#include "NavigationController.hpp"
#include "Viper/iOSutil/NS/Array.hpp"
#include "Viper/iOSutil/NS/Dictionary.hpp"
#include <map>
#include <functional>

namespace UI {
    struct ImagePickerController:public UI::NavigationController{
        using NavigationController::NavigationController;
#ifdef __APPLE__
        STATIC_VAR(const std::string, className, "UIImagePickerController");
        
        typedef std::function<void(UI::ImagePickerController)> DidCancel;
        typedef std::function<void(UI::ImagePickerController,NS::Dictionary)> DidFinishPickingMediaWithInfo;
        
        enum class SourceType{
            PhotoLibrary = UIImagePickerControllerSourceTypePhotoLibrary,
            Camera = UIImagePickerControllerSourceTypeCamera,
            SavedPhotosAlbum = UIImagePickerControllerSourceTypeSavedPhotosAlbum,
        };
        
        static UI::ImagePickerController create(){
            auto cls=NS::getClass(className());
            assert(cls);
            auto handle=sendMessage<Handle>(cls, "new");
            ImagePickerController res(handle);
            return std::move(res);
        }
        
        static bool isSourceTypeAvailable(UI::ImagePickerController::SourceType sourceType){
            auto cls=NS::getClass(className());
            return sendMessage<BOOL>(cls,"isSourceTypeAvailable:", UIImagePickerControllerSourceType(sourceType));
        }
        
        static NS::Array availableMediaTypesForSourceType(UI::ImagePickerController::SourceType sourceType){
            auto cls=NS::getClass(className());
            return sendMessage<Handle>(cls,"availableMediaTypesForSourceType:", UIImagePickerControllerSourceType(sourceType));
        }
        
        static NS::String OriginalImage(){
            auto res=CFBridgingRetain(UIImagePickerControllerOriginalImage);
            CFRelease(res);
            return res;
        }
        
        void setDidCancel(DidCancel f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIImagePickerControllerDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).didCancel=f;
        }
        
        void setDidFinishPickingMediaWithInfo(DidFinishPickingMediaWithInfo f){
            if(!DelegateEventHandler::get(this->handle)){
                auto sharedEventHandlerClass=NS::getClass("UIImagePickerControllerDelegateEventHandler");
                auto sharedEventHandler=NS::Object::sendMessage<Handle>(sharedEventHandlerClass,"shared");
                this->sendMessage<void>("setDelegate:", sharedEventHandler);
            }
            DelegateEventHandler::getOrCreate(this->handle).didFinishPickingMediaWithInfo=f;
        }
        
        void setMediaTypes(const NS::Array &newValue){
            this->sendMessage<void>("setMediaTypes:", newValue.handle);
        }
        
        NS::Array mediaTypes(){
            return this->sendMessage<Handle>("mediaTypes");
        }
        
        void setSourceType(UI::ImagePickerController::SourceType newValue){
            this->sendMessage<void>("setSourceType:", UIImagePickerControllerSourceType(newValue));
        }
        
        SourceType sourceType(){
            return SourceType(this->sendMessage<UIImagePickerControllerSourceType>("sourceType"));
        }
        
        struct DelegateEventHandler{
            DidCancel didCancel;
            DidFinishPickingMediaWithInfo didFinishPickingMediaWithInfo;
            
            static void imagePickerControllerDidCancel(const void *sender){
                if(auto d=get(sender)){
                    if(d->didCancel){
                        d->didCancel(sender);
                    }
                    DelegateEventHandler::remove(sender);
                }
            }
            
            static void imagePickerControllerDidFinishPickingMediaWithInfo(const void *sender,const void *info){
                if(auto d=get(sender)){
                    if(d->didFinishPickingMediaWithInfo){
                        d->didFinishPickingMediaWithInfo(sender,info);
                    }
                    DelegateEventHandler::remove(sender);
                }
            }
            
            static DelegateEventHandler& getOrCreate(const void *sender){
                auto it=delegateEventHandlers().find(sender);
                if(it != delegateEventHandlers().end()){
                    return it->second;
                }else{
                    return delegateEventHandlers().insert({sender,{}}).first->second;
                }
            }
            
            static DelegateEventHandler* get(const void *aw){
                auto it=delegateEventHandlers().find(aw);
                if(it != delegateEventHandlers().end()){
                    return &it->second;
                }else{
                    return nullptr;
                }
            }
            
        protected:
            typedef std::map<Handle, DelegateEventHandler> DelegateEventHandlersMap;
            STATIC_VAR(DelegateEventHandlersMap, delegateEventHandlers, {});
            
            static void remove(const void *aw){
                auto it=delegateEventHandlers().find(aw);
                if(it != delegateEventHandlers().end()){
                    delegateEventHandlers().erase(it);
                }
            }
        };
        
#endif
    };
}
