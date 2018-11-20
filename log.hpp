//
//  log.hpp
//  logging
//
//  Created by Stijn Frishert on 11/18/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <chrono>
#include <ctime>
#include <string_view>
#include <utility>

namespace lj
{
    template <typename... Args>
    class Log
    {
    public:
        virtual ~Log() = default;
        
        void log(Args... args);
        void log(std::time_t time, Args... args);
        
    private:
        virtual void flush(std::time_t time, Args... args) = 0;
    };

    template <typename... Args>
    void Log<Args...>::log(Args... args)
    {
        using namespace std::chrono;
        
        flush(system_clock::to_time_t(system_clock::now()), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Log<Args...>::log(std::time_t time, Args... args)
    {
        flush(time, std::forward<Args>(args)...);
    }
}
