//
//  datetime_formatter.cpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#include <array>

#include "datetime_formatter.hpp"

namespace lj
{
    DateTimeFormatter::DateTimeFormatter(std::string_view format) :
        format(format)
    {
        
    }

    std::string DateTimeFormatter::operator()(std::time_t time)
    {
        const auto tm = std::localtime(&time);
        
        std::array<char, 9> timeBuffer;
        timeBuffer.fill('\0');
        std::strftime(timeBuffer.data(), timeBuffer.size(), format.data(), tm);
        
        return timeBuffer.data();
    }

    DateTimeFormatter DateTimeFormatter::hourMinute("%R");
    DateTimeFormatter DateTimeFormatter::hourMinuteSecond("%T");
}
