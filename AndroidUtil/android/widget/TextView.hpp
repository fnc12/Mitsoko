
#ifndef __VIPER__ANDROID_UTIL__ANDROID__WIDGET__TEXT_VIEW__
#define __VIPER__ANDROID_UTIL__ANDROID__WIDGET__TEXT_VIEW__

#include "Viper/AndroidUtil/android/view/View.hpp"
#include "Viper/AndroidUtil/java/lang/String.hpp"
#include "Viper/AndroidUtil/android/graphics/Color.hpp"
#include "Viper/AndroidUtil/android/text/TextWatcher.hpp"
#include "Viper/AndroidUtil/android/text/Editable.hpp"
#include "Viper/Disposable.hpp"
#include <functional>
#include <map>
#include <vector>

namespace android{
    
    namespace widget{
        
        struct TextView:public view::View{
            
            using View::View;
            
#ifdef __ANDROID__
            
//            const std::string signature;
            STATIC_VAR(const std::string, signature, "android/widget/TextView");
            
            typedef std::function<void(java::lang::CharSequence,int,int,int)> OnTextChanged;
            typedef std::function<void(java::lang::CharSequence,int,int,int)> BeforeTextChanged;
            typedef std::function<void(android::text::Editable)> AfterTextChanged;
            
            void setInputType(int type);
            
            void setTextColor(int color);
            
            void setText(const std::string &value);
            
//            void setText(const java::lang::String &str);
            
            void setHint(const std::string &value);
            
            std::string getHint();
            
            void addTextChangedListener(const android::text::TextWatcher &watcher);
            
            /**
             *  This is a c++ adaptation of `addTextChangedListener` function. You do not
             *  have to create a TextWatcher object - just set lambdas and that's all. 
             *  Any lambda can be nullptr.
             */
            void addTextChangedListener(OnTextChanged onTextChanged,
                                        BeforeTextChanged beforeTextChanged,
                                        AfterTextChanged afterTextChanged,
                                        const Viper::Disposable &disposable);
            
            struct TextWatcherEventHandler{
                typedef std::map<int,OnTextChanged> OnTextChangedMap;
                static OnTextChangedMap onTextChangedMap;
                
                typedef std::map<int,BeforeTextChanged> BeforeTextChangedMap;
                static BeforeTextChangedMap beforeTextChangedMap;
                
                typedef std::map<int,AfterTextChanged> AfterTextChangedMap;
                static AfterTextChangedMap afterTextChangedMap;
                
                typedef std::map<Viper::Disposable::Id,std::vector<int>> DisposablesMap;
                static DisposablesMap disposablesMap;
                
                struct Observer : public Viper::Disposable::Observer {
                    
                    Observer();
                    
                    virtual void disposableDidDispose(Viper::Disposable::Id id) override;
                };
                
                static Observer observer;
                
                static void textViewOnTextChanged(int textWatcherId,jobject s,int start, int before, int count);
                
                static void textViewBeforeTextChanged(int textWatcherId,jobject s,int start, int before, int count);
                
                static void textViewAfterTextChanged(int textWatcherId,jobject e);
            };
            
#endif  //__ANDROID__
            
        };
    }
}

#endif  //__VIPER__ANDROID_UTIL__ANDROID__WIDGET__TEXT_VIEW__
