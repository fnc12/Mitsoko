
#pragma once

#include <string>
#include <mutex>
#include "iOSutil/iOSutil.hpp"
#include "AndroidUtil/AndroidUtil.hpp"
#include "R/Strings.hpp"

namespace Viper{
    struct Language{
        static const std::string& current();
        
        static void setCurrent(const std::string &newValue);
    protected:
        static std::string _current;
        
        static std::mutex languageOnceMutex;
    };
    
    std::string localizedString(const std::string &key,const std::string &lang);
    
    std::string localizedString(const std::string &key);
    
    /**
     *  Localized string syntax sugar.
     */
    std::string operator"" _ls (const char *s,size_t len);
    
    /**
     *  Functor for lambda replacing in STL algorithms.
     */
    struct Localizator{
        std::string operator()(const std::string &s) const;
    };
}
