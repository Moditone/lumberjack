//
//  stream_log.hpp
//  logging
//
//  Created by Stijn Frishert on 11/18/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <iostream>
#include <utility>

#include "formatter.hpp"
#include "log.hpp"
#include "delimiting_formatter.hpp"

namespace lj
{
    template <typename... Args>
    class StreamLog :
        public Log<Args...>
    {
    public:
        StreamLog(Formatter<Args...>& formatter, std::ostream& stream);
        
    public:
        static StreamLog cout;
        static StreamLog cerr;
        static StreamLog clog;
        
    private:
        void flush(std::time_t time, Args... args) final;
        
    private:
        Formatter<Args...>& formatter;
        std::ostream& stream;
    };

    template <typename... Args>
    StreamLog<Args...>::StreamLog(Formatter<Args...>& formatter, std::ostream& stream) :
        formatter(formatter),
        stream(stream)
    {
        
    }

    template <typename... Args>
    void StreamLog<Args...>::flush(std::time_t time, Args... args)
    {
        stream << formatter(time, std::forward<Args>(args)...) << std::endl;
    }

    template <typename... Args>
    StreamLog<Args...> StreamLog<Args...>::cout(DelimitingFormatter<Args...>::space, std::cout);

    template <typename... Args>
    StreamLog<Args...> StreamLog<Args...>::cerr(DelimitingFormatter<Args...>::space,std::cerr);

    template <typename... Args>
    StreamLog<Args...> StreamLog<Args...>::clog(DelimitingFormatter<Args...>::space,std::clog);
}
