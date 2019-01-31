//
//  file_log.hpp
//  logging
//
//  Created by Stijn Frishert on 11/18/18.
//  Copyright © 2018 moditone. All rights reserved.
//

#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

#include "formatter.hpp"
#include "log.hpp"

namespace lj
{
    template <typename... Args>
    class FileLog :
        public Log<Args...>
    {
    public:
        FileLog(Formatter<Args...>& formatter, std::string_view path);

    public:
        Formatter<Args...>& formatter;
        const std::string path;
        
    private:
        void flush(std::time_t time, Args... args) final;
        
    private:
        std::ofstream stream;
    };

    template <typename... Args>
    FileLog<Args...>::FileLog(Formatter<Args...>& formatter, std::string_view path) :
        formatter(formatter),
        path(path),
        stream(path.data())
    {
        if (!stream.is_open())
        {
            std::stringstream stream;
            stream << "could not open '" << path << "'";
            throw std::runtime_error(stream.str());
        }
    }

    template <typename... Args>
    void FileLog<Args...>::flush(std::time_t time, Args... args)
    {
        stream << formatter(time, std::forward<Args>(args)...) << std::endl;
    }
}
