//
//  Dictionary.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "Dictionary.hpp"

#ifdef __APPLE__

const std::string NS::Dictionary::className="NSDictionary";

NS::Object NS::Dictionary::objectForKey(const NS::Object &aKey){
    return this->sendMessage<Handle>("objectForKey:", aKey.handle);
}

int NS::Dictionary::count(){
    return int(this->sendMessage<NSUInteger>("count"));
}

NS::Dictionary::ValueAdapter::ValueAdapter(decltype(dictionary)d,decltype(key)k):dictionary(d),key(k){}

NS::Dictionary::ValueAdapter::operator NS::Object() const{
    return dictionary.objectForKey(this->key);
}

auto NS::Dictionary::operator[](const NS::Object &key)->ValueAdapter{
    return ValueAdapter{*this,key};
}

#endif  //__APPLE__
