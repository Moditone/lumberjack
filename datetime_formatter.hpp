//
//  datetime_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <array>
#include <string>
#include <string_view>

#include "time_formatter.hpp"

namespace lj
{
    class DateTimeFormatter :
        public TimeFormatter
    {
    public:
        DateTimeFormatter(std::string_view format) :
            format(format)
        {
            
        }
        
        std::string operator()(std::time_t time) final
        {
            const auto tm = std::localtime(&time);
            
            std::array<char, 9> timeBuffer;
            timeBuffer.fill('\0');
            std::strftime(timeBuffer.data(), timeBuffer.size(), format.data(), tm);
            
            return timeBuffer.data();
        }
        
    public:
        std::string format;
        
        static DateTimeFormatter& hourMinute() { static DateTimeFormatter fmt("%R"); return fmt; }
        static DateTimeFormatter& hourMinuteSecond() { static DateTimeFormatter fmt("%T"); return fmt; }
    };
}
