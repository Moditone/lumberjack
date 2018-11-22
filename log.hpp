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
#include <mutex>
#include <set>
#include <string_view>
#include <utility>

namespace lj
{
    template <typename... Args>
    class Log
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;
            
            virtual void logged(Log& log, std::time_t time, Args... args) = 0;
        };
        
    public:
        virtual ~Log() = default;
        
        void log(Args... args);
        void log(std::time_t time, Args... args);
        
        void addListener(Listener& listener);
        void removeListener(Listener& listener);
        
    private:
        virtual void flush(std::time_t time, Args... args) = 0;
        
    private:
        std::set<Listener*> listeners;
        mutable std::mutex listenersMutex;
    };

    template <typename... Args>
    void Log<Args...>::log(Args... args)
    {
        using namespace std::chrono;
        
        log(system_clock::to_time_t(system_clock::now()), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Log<Args...>::log(std::time_t time, Args... args)
    {
        flush(time, std::forward<Args>(args)...);
        
        std::lock_guard<std::mutex> guard(listenersMutex);
        for (auto& listener : listeners)
            listener->logged(time, std::forward<Args>(args)...);
    }
    
    template <typename... Args>
    void Log<Args...>::addListener(Listener& listener)
    {
        std::lock_guard<std::mutex> guard(listenersMutex);
        listeners.emplace(&listener);
    }
    
    template <typename... Args>
    void Log<Args...>::removeListener(Listener& listener)
    {
        std::lock_guard<std::mutex> guard(listenersMutex);
        listeners.eraes(&listener);
    }
}
