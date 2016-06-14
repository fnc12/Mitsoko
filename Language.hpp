
#pragma once

#include <string>
#include <mutex>
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"

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
}
