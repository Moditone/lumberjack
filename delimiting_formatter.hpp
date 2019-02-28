//
//  delimiting_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <ios>
#include <sstream>
#include <string>

#include "formatter.hpp"
#include "time_formatter.hpp"
#include "date_time_formatter.hpp"

namespace lj
{
    template <typename... Args>
    class DelimitingFormatter :
        public Formatter<Args...>
    {
    public:
        DelimitingFormatter(TimeFormatter& timeFormatter, std::string_view delimiter);
        
        std::string operator()(std::time_t time, Args... args) final;
        
        static DelimitingFormatter space;
        static DelimitingFormatter comma;
        
    public:
        TimeFormatter& timeFormatter;
        std::string delimiter = " ";
    };
    
    template <typename... Args>
    DelimitingFormatter<Args...>::DelimitingFormatter(TimeFormatter& timeFormatter, std::string_view delimiter) :
        timeFormatter(timeFormatter),
        delimiter(delimiter)
    {
        
    }
    
    template <typename... Args>
    std::string DelimitingFormatter<Args...>::operator()(std::time_t time, Args... args)
    {
        std::stringstream stream;
        stream << timeFormatter(time);
        stream.setf(std::ios_base::fixed | std::ios_base::boolalpha);
        ((stream << delimiter << args), ...);
        
        return stream.str();
    }
    
    template <typename... Args>
    DelimitingFormatter<Args...> DelimitingFormatter<Args...>::space(DateTimeFormatter::hourMinuteSecond(), " ");
    
    template <typename... Args>
    DelimitingFormatter<Args...> DelimitingFormatter<Args...>::comma(DateTimeFormatter::hourMinuteSecond(), ",");
}
