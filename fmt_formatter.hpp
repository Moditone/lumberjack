//
//  fmt_formatter.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <fmt/format.h>
#include <fmt/time.h>

#include "formatter.hpp"
#include "time_formatter.hpp"

namespace lj
{
    template <typename... Args>
    class FmtFormatter :
        public Formatter<Args...>
    {
    public:
        FmtFormatter(TimeFormatter& timeFormatter);
        
        std::string operator()(std::time_t time, Args... args) final;
        
    public:
        TimeFormatter& timeFormatter;
        std::string format;
    };

    template <typename... Args>
    FmtFormatter<Args...>::FmtFormatter(TimeFormatter& timeFormatter) :
        timeFormatter(timeFormatter)
    {
        for (auto i = 0; i < sizeof...(Args); i++)
            format += " {}";
    }

    template <typename... Args>
    std::string FmtFormatter<Args...>::operator()(std::time_t time, Args... args)
    {
        return timeFormatter(time) + fmt::format(format, args...);
    }
}
