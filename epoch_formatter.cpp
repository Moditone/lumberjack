//
//  epoch_formatter.cpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#include <sstream>

#include "epoch_formatter.hpp"

namespace lj
{
    EpochFormatter::EpochFormatter(std::time_t epoch) :
        epoch(epoch)
    {
        
    }

    std::string EpochFormatter::operator()(std::time_t time)
    {
        const auto diff = std::difftime(time, epoch);
        
        std::stringstream stream;
        stream.precision(precision);
        stream << std::fixed << diff;
        
        return stream.str();
    }
}
