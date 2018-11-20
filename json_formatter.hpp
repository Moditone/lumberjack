//
//  json_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <string>

#include <moditone/jsonata/writer.hpp>

#include "formatter.hpp"
#include "time_formatter.hpp"

namespace lj
{
    template <typename... Args>
    class JsonFormatter :
        public Formatter<Args...>
    {
    public:
        JsonFormatter(TimeFormatter& timeFormatter, json::Writer& writer);
        
        std::string operator()(std::time_t time, Args... args);
        
    public:
        std::string timeKey = "time";
        std::string dataKey = "data";
        
    private:
        TimeFormatter& timeFormatter;
        json::Writer& writer;
    };

    template <typename... Args>
    JsonFormatter<Args...>::JsonFormatter(TimeFormatter& timeFormatter, json::Writer& writer) :
        timeFormatter(timeFormatter),
        writer(writer)
    {
        
    }

    template <typename... Args>
    std::string JsonFormatter<Args...>::operator()(std::time_t time, Args... args)
    {
        json::Value json;
        json[timeKey] = timeFormatter(time);
        
        if constexpr (sizeof...(Args) == 1)
        {
            json.insert(dataKey, std::forward<Args>(args)...);
        } else {
            (json[dataKey].append(args), ...);
        }
        
        return writer.writeToString(json);
    }
}
