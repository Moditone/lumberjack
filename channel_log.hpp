//
//  channel_log.hpp
//  logging
//
//  Created by Stijn Frishert on 11/20/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "log.hpp"

namespace lj
{
    template <typename... Args>
    class ChannelLog
    {
    public:
        bool addLog(std::string_view name, Log<Args...>& log)
        {
            return logs.emplace(std::string{name}, log).second;
        }

        void removeLog(std::string_view name)
        {
            logs.erase(std::string{name});
        }

        template <typename... Args2>
        void log(std::string_view name, Args2... args)
        {
            (*this)[name](std::forward<Args2>(args)...);
        }

        template <typename... Args2>
        void operator()(Args2... args)
        {
            log(std::forward<Args2>(args)...);
        }

        Log<Args...>& operator[](std::string_view name)
        {
            return logs.at(std::string{name});
        }

        const Log<Args...>& operator[](std::string_view name) const
        {
            return logs.at(std::string{name});
        }

        std::size_t size() const { return logs.size(); }
        bool empty() const { return empty(); }

    private:
        std::unordered_map<std::string, std::reference_wrapper<Log<Args...>>> logs;
    };
}
