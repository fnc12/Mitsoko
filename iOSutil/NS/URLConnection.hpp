//
//  URLConnection.hpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#ifndef URLConnection_hpp
#define URLConnection_hpp

#include "Object.hpp"
#include "Data.hpp"
#include "URLRequest.hpp"
#include "URLResponse.hpp"
#include "Error.hpp"
#include "OperationQueue.hpp"

namespace NS {
    
    struct URLConnection : public NS::Object {
        
        using Object::Object;
        
#ifdef __APPLE__
        
        static const std::string className;
        
        static NS::Data sendSynchronousRequest(const NS::URLRequest &request,
                                               NS::URLResponse *returningResponse,
                                               NS::Error *error);
        
        static void sendAsynchronousRequest(const NS::URLRequest &request,
                                            const NS::OperationQueue &queue,
                                            std::function<void(NS::URLResponse, NS::Data, NS::Error)> completionHandler);
        
#endif  //__APPLE__
    };
}

#endif /* URLConnection_hpp */
