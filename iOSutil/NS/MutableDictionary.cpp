//
//  MutableDictionary.cpp
//  Groozim
//
//  Created by John Zakharov on 14.08.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "MutableDictionary.hpp"

#ifdef __APPLE__

const std::string NS::MutableDictionary::className="NSMutableDictionary";

NS::MutableDictionary NS::MutableDictionary::create(){
    auto cls=NS::getClass(className);
    assert(cls);
    auto handle=sendMessage<Handle>(cls, "new");
    return handle;
}

void NS::MutableDictionary::setObject(const NS::Object &anObject,const NS::Object &aKey){
    this->sendMessage<void>("setObject:forKey:", anObject.handle, aKey.handle);
}

void NS::MutableDictionary::removeObjectForKey(const NS::Object &aKey){
    this->sendMessage<void>("removeObjectForKey:", aKey.handle);
}

NS::MutableDictionary::ValueAdapter::ValueAdapter(decltype(dictionary)d,decltype(key)k):dictionary(d),key(k){}

NS::MutableDictionary::ValueAdapter::operator NS::Object() const{
    return dictionary.objectForKey(this->key);
}

void NS::MutableDictionary::ValueAdapter::operator=(NS::Object value){
    dictionary.setObject(value, this->key);
}

auto NS::MutableDictionary::operator[](const NS::Object &key)->ValueAdapter{
    return ValueAdapter{*this,key};
}

#endif  //__APPLE__
