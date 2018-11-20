//
//  formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <ctime>
#include <string>

namespace lj
{
    template <typename... Args>
    class Formatter
    {
    public:
        virtual ~Formatter() = default;
        
        virtual std::string operator()(std::time_t time, Args...) = 0;
    };
}
