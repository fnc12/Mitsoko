//
//  UrlResponse.hpp
//  Groozim
//
//  Created by John Zakharov on 21.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef VIPER__URL_RESPONSE
#define VIPER__URL_RESPONSE

#include <string>

#ifdef __APPLE__
#include "Mitsoko/iOSutil/NS/HTTPURLResponse.hpp"
#else
#include "Mitsoko/AndroidUtil/java/lang/Object.hpp"
#endif  //__APPLE__

namespace Mitsoko {
    
    namespace Url {
        
        class Request;
        
        struct Response {
            
            int statusCode();
            
            std::string statusDescription();
            
            operator bool () const;
            
        protected:
            
#ifdef __APPLE__
            NS::HTTPURLResponse response;
#else
            java::lang::Object response;
#endif
            Response(decltype(response));
            
            friend class Request;
            
        };
    }
}

#endif //VIPER__URL_RESPONSE
