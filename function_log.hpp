//
//  file_log.hpp
//  logging
//
//  Created by Stijn Frishert on 11/18/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <functional>

#include "formatter.hpp"
#include "log.hpp"

namespace lj
{
    template <typename... Args>
    class FunctionLog :
        public Log<Args...>
    {
    public:
        std::function<void(std::time_t, Args...)> onLog;
        
    private:
        void flush(std::time_t time, Args... args) final;
    };
    template <typename... Args>
    void FunctionLog<Args...>::flush(std::time_t time, Args... args)
    {
        if (onLog)
            onLog(time, std::forward<Args>(args)...);
    }
}
