
#pragma once

#include <string>
#include <mutex>
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"
#include "R/Strings.hpp"

namespace Viper{
    struct Language{
        static const std::string& current(){
            static std::string res="";
            if(!res.length()){
                languageOnceMutex().lock();
#ifdef __APPLE__
                NS::String currentLanguage=NS::Bundle::mainBundle().preferredLocalizations()[0];
                res=currentLanguage.UTF8String();
#else
                auto language=java::util::Locale::getDefault().getLanguage();
                res=language.c_str();
#endif
                languageOnceMutex().unlock();
            }
            return res;
        }
    protected:
        static std::mutex& languageOnceMutex(){
            static std::mutex res;
            return res;
        }
    };
    
    inline std::string localizedString(const std::string &key){
        auto c=Language::current();
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
        }
    }
    
    /**
     *  Localized string syntax sugar.
     */
    inline std::string operator"" _ls (const char *s,size_t len){
        return localizedString({s,len});
    }
}
