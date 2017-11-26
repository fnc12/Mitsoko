//
//  SearchBar.hpp
//  mitsoko_ios
//
//  Created by John Zakharov on 20.11.2017.
//  Copyright © 2017 Mitsoko. All rights reserved.
//

#ifndef __Mitsoko__ios_util__ui__search_bar__
#define __Mitsoko__ios_util__ui__search_bar__

#include "View.hpp"

namespace UI {
    
    struct SearchBar : public UI::View {
        using View::View;
        
#ifdef __APPLE__
        
        static const std::string className;
        
#endif  //  __APPLE__
    };
}

#endif /* __Mitsoko__ios_util__ui__search_bar__ */
