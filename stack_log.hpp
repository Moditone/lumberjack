//
//  log_stack.hpp
//  logging
//
//  Created by Stijn Frishert on 11/18/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <functional>
#include <initializer_list>
#include <unordered_set>
#include <utility>

#include "log.hpp"

namespace lj
{
    template <typename... Args>
    class StackLog :
        public Log<Args...>
    {
    public:
        StackLog() = default;
        StackLog(std::initializer_list<std::reference_wrapper<Log<Args...>>> logs);
        
        void addLog(Log<Args...>& log);
        void removeLog(Log<Args...>& log);
        
    private:
        void flush(std::time_t time, Args... args) final;
        
    private:
        std::unordered_set<Log<Args...>*> logs;
    };

    template <typename... Args>
    StackLog<Args...>::StackLog(std::initializer_list<std::reference_wrapper<Log<Args...>>> logs)
    {
        for (auto& log : logs)
            addLog(log.get());
    }

    template <typename... Args>
    void StackLog<Args...>::addLog(Log<Args...>& log)
    {
        logs.emplace(&log);
    }

    template <typename... Args>
    void StackLog<Args...>::removeLog(Log<Args...>& log)
    {
        logs.erase(&log);
    }

    template <typename... Args>
    void StackLog<Args...>::flush(std::time_t time, Args... args)
    {
        for (auto& log : logs)
            log->log(time, std::forward<Args>(args)...);
    }
}
