//
//  epoch_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <ctime>

#include "time_formatter.hpp"

namespace lj
{
    class EpochFormatter :
        public TimeFormatter
    {
    public:
        EpochFormatter() = default;
        EpochFormatter(std::time_t epoch);
        
        std::string operator()(std::time_t time) final;
        
    public:
        std::time_t epoch = std::chrono::system_clock::to_time_t({});
        unsigned short precision = 0;
    };
}
