
#pragma once

#include <string>
#include <mutex>
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"
#include "R/Strings.hpp"

namespace Viper{
    struct Language{
        static const std::string& current(){
            if(!_current().length()){
                languageOnceMutex().lock();
#ifdef __APPLE__
                NS::String currentLanguage=NS::Bundle::mainBundle().preferredLocalizations()[0];
                _current()=currentLanguage.UTF8String();
#else
                auto language=java::util::Locale::getDefault().getLanguage();
                _current()=language.c_str();
#endif
                languageOnceMutex().unlock();
            }
            return _current();
        }
        
        static void setCurrent(const std::string &newValue){
            _current()=newValue;
        }
    protected:
        static std::string& _current(){
            static std::string res;
            return res;
        }
        
        static std::mutex& languageOnceMutex(){
            static std::mutex res;
            return res;
        }
    };
    
    inline std::string localizedString(const std::string &key,const std::string &lang){
        if(lang.length()){
            auto mapIt=R::localizedStrings().find(lang);
            if(mapIt != R::localizedStrings().end()){
                auto pIt=mapIt->second.find(key);
                if(pIt != mapIt->second.end()){
                    return pIt->second;
                }else{
                    return key;
                }
            }else{
                return key;
            }
        }else{
            return key;
        }
    }
    
    inline std::string localizedString(const std::string &key){
        return std::move(localizedString(key,Language::current()));
        /*auto c=Language::current();
        if(c.length()){
            auto mapIt=R::localizedStrings().find(c);
            if(mapIt != R::localizedStrings().end()){
                auto pIt=mapIt->second.find(key);
                if(pIt != mapIt->second.end()){
                    return pIt->second;
                }else{
                    return key;
                }
            }else{
                return key;
            }
        }else{
            return key;
        }*/
    }
    
    /**
     *  Localized string syntax sugar.
     */
    inline std::string operator"" _ls (const char *s,size_t len){
        return localizedString({s,len});
    }
    
    /**
     *  Functor for lambda replacing in STL algorithms.
     */
    struct Localizator{
        auto operator()(const std::string &s) const{
            return std::move(localizedString(s));
        }
    };
}
