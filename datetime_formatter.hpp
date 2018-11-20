//
//  datetime_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include "time_formatter.hpp"

namespace lj
{
    class DateTimeFormatter :
        public TimeFormatter
    {
    public:
        DateTimeFormatter(std::string_view format);
        
        std::string operator()(std::time_t time) final;
        
    public:
        std::string format;
        
        static DateTimeFormatter hourMinute;
        static DateTimeFormatter hourMinuteSecond;
    };
}
