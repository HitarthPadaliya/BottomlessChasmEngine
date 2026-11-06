#pragma once

#include <iostream>
#include <string>
#include <source_location>


namespace Color
{
    constexpr const char* Reset         = "\033[0m";
    constexpr const char* Bold          = "\033[1m";

    constexpr const char* Red           = "\033[31m";
    constexpr const char* Yellow        = "\033[33m";
    constexpr const char* Green         = "\033[32m";
    constexpr const char* Cyan          = "\033[36m";
    constexpr const char* White         = "\033[37m";
    constexpr const char* Magenta       = "\033[35m";

    constexpr const char* BoldRed       = "\033[1;31m";
    constexpr const char* BoldYellow    = "\033[1;33m";
    constexpr const char* BoldGreen     = "\033[1;32m";
    constexpr const char* BoldCyan      = "\033[1;36m";
    constexpr const char* BoldMagenta   = "\033[1;35m";
}


enum class LogLevel
{
    None,
    Info,
    Success,
    Warning,
    Error,
    Vulkan,
    Section,
};


class Logger
{
    public:
        static void Log(LogLevel level, const std::string& message, const std::source_location loc = std::source_location::current());
    
		static void Log    (const std::string& msg, const std::source_location loc = std::source_location::current());
        static void Info    (const std::string& msg, const std::source_location loc = std::source_location::current());
        static void Success (const std::string& msg, const std::source_location loc = std::source_location::current());
        static void Warn    (const std::string& msg, const std::source_location loc = std::source_location::current());
        static void Error   (const std::string& msg, const std::source_location loc = std::source_location::current());
        static void Vulkan  (const std::string& msg, const std::source_location loc = std::source_location::current());
        static void Section (const std::string& msg, const std::source_location loc = std::source_location::current());
};
