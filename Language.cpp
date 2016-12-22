//
//  Language.cpp
//  Jako
//
//  Created by John Zakharov on 06.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Language.hpp"

std::string Viper::Language::_current;

std::mutex Viper::Language::languageOnceMutex;

const std::string& Viper::Language::current(){
    if(!_current.length()){
        languageOnceMutex.lock();
#ifdef __APPLE__
        NS::String currentLanguage=NS::Bundle::mainBundle().preferredLocalizations()[0];
        _current=currentLanguage.UTF8String();
#else
        auto language=java::util::Locale::getDefault().getLanguage();
        _current=language.c_str();
#endif
        languageOnceMutex.unlock();
    }
    return _current;
}

void Viper::Language::setCurrent(const std::string &newValue){
    _current=newValue;
}

std::string Viper::localizedString(const std::string &key,const std::string &lang){
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

std::string Viper::localizedString(const std::string &key){
    return localizedString(key,Language::current());
}

std::string Viper::operator"" _ls (const char *s,size_t len){
    return localizedString({s,len});
}

std::string Viper::Localizator::operator()(const std::string &s) const{
    return localizedString(s);
}
