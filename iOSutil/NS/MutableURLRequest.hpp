//
//  MutableURLRequest.hpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef MutableURLRequest_hpp
#define MutableURLRequest_hpp

#include "URLRequest.hpp"
#include "Data.hpp"

namespace NS {
    
    struct MutableURLRequest : public NS::URLRequest{
        
        using URLRequest::URLRequest;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        static NS::MutableURLRequest create();
        
        void setURL(const NS::URL &newValue);
        
        void setHTTPBody(const NS::Data &newValue);
        
        NS::Data HTTPBody();
        
        void setHTTPMethod(const NS::String &newValue);
        
        void setHTTPMethod(const std::string &newValue);
        
        void setHTTPMethod(const char *newValue);
        
        void setValueForHTTPHeaderField(const NS::String &value, const NS::String &field);
        
        void setValueForHTTPHeaderField(const std::string &value,const std::string &field);
        
#endif
    };
}

#endif /* MutableURLRequest_hpp */
