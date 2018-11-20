//
//  csv_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <algorithm>
#include <sstream>
#include <string>

#include "delimiting_formatter.hpp"
#include "formatter.hpp"
#include "time_formatter.hpp"

namespace lj
{
    namespace
    {
        template <typename, typename Replacement>
        struct Replace
        {
            using type = Replacement;
        };
    }

    std::string canonizeCsv(std::string&& string);

    class CsvTimeFormatter :
        public TimeFormatter
    {
    public:
        CsvTimeFormatter(TimeFormatter& formatter);
        
        std::string operator()(std::time_t time) final;
        
    private:
        TimeFormatter& formatter;
    };

    template <typename... Args>
    class CsvFormatter :
        public Formatter<Args...>
    {
    public:
        CsvFormatter(TimeFormatter& timeFormatter);
        
        std::string operator()(std::time_t time, Args... args) final;
        
    private:
        template <typename T>
        std::string toString(const T& value);
        
    private:
        CsvTimeFormatter csvTimeFormatter;
        
        // A formatter with string_view for every type in Args
        DelimitingFormatter<typename Replace<Args, std::string_view>::type...> delimitingFormatter;
    };

    template <typename... Args>
    CsvFormatter<Args...>::CsvFormatter(TimeFormatter& timeFormatter) :
        csvTimeFormatter(timeFormatter),
        delimitingFormatter(csvTimeFormatter, ",")
    {
        
    }

    template <typename... Args>
    std::string CsvFormatter<Args...>::operator()(std::time_t time, Args... args)
    {
        return delimitingFormatter(time, toString(args)...);
    }

    template <typename... Args>
    template <typename T>
    std::string CsvFormatter<Args...>::toString(const T& value)
    {
        std::stringstream stream;
        stream << value;
        return canonizeCsv(stream.str());
    }
}
