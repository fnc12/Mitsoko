//
//  URLConnection.cpp
//  Groozim
//
//  Created by John Zakharov on 12.11.16.
//  Copyright © 2016 Outlaw Studio. All rights reserved.
//

#include "URLConnection.hpp"

#ifdef __APPLE__

const std::string NS::URLConnection::className = "NSURLConnection";

NS::Data NS::URLConnection::sendSynchronousRequest(const NS::URLRequest &request, NS::URLResponse *returningResponse, NS::Error *error) {
    auto cls = NS::getClass(className);
    assert(cls);
    return sendMessage<Handle>(cls,
                               "sendSynchronousRequest:returningResponse:error:",
                               request.handle,
                               returningResponse ? &returningResponse->handle : nullptr,
                               error ? &error->handle : nullptr);
}

void NS::URLConnection::sendAsynchronousRequest(const NS::URLRequest &request,
                                                const NS::OperationQueue &queue,
                                                std::function<void(NS::URLResponse, NS::Data, NS::Error)> completionHandler)
{
    [NSURLConnection sendAsynchronousRequest:(__bridge id)request.handle
                                       queue:(__bridge id)queue.handle
                           completionHandler:^(NSURLResponse * _Nullable response, NSData * _Nullable data, NSError * _Nullable connectionError) {
     if(completionHandler){
     completionHandler((__bridge Handle)response,
                       (__bridge Handle)data,
                       (__bridge Handle)connectionError);
     }
     }];
}

#endif  //__APPLE__
