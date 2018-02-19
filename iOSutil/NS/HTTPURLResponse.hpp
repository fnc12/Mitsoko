
#ifndef HTTPURLResponse_hpp
#define HTTPURLResponse_hpp

#include "URLResponse.hpp"
#include "String.hpp"
#include "Mitsoko/iOSutil/NS/Dictionary.hpp"

namespace NS {
    
    struct HTTPURLResponse : public NS::URLResponse {
        
        using URLResponse::URLResponse;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        int statusCode();
        
        NS::Dictionary allHeaderFields();
        
        static NS::String localizedStringForStatusCode(int statusCode);
        
#endif  //__APPLE__
        
    };
}

#endif /* HTTPURLResponse_hpp */
