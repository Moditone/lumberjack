//
//  time_formatter.hpp
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
    class TimeFormatter
    {
    public:
        virtual ~TimeFormatter() = default;
        
        virtual std::string operator()(std::time_t time) = 0;
    };
}
