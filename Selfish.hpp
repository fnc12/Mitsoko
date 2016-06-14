
#pragma once

template<class T>
struct Selfish{
    T &self;
    
    Selfish():self(static_cast<T&>(*this)){}
};
