//
//  csv_formatter.cpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#include "csv_formatter.hpp"

namespace lj
{
    std::string canonizeCsv(std::string&& string)
    {
        if (!std::any_of(string.begin(), string.end(), [](auto c){ return c == ',' || c == '"'; }))
            return std::move(string);
        
        std::stringstream stream;
        stream << '"';
        for (auto& c : string)
        {
            if (c == '"')
                stream << '"';
            stream << c;
        }
        stream << '"';
        
        return stream.str();
    }

    CsvTimeFormatter::CsvTimeFormatter(TimeFormatter& formatter) :
        formatter(formatter)
    {
        
    }

    std::string CsvTimeFormatter::operator()(std::time_t time)
    {
        return canonizeCsv(formatter(time));
    }
}
