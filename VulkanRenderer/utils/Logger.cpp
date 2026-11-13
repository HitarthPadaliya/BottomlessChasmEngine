#include "pch.h"
#include "Logger.h"


void Logger::Log(LogLevel level, const std::string_view& message, const std::source_location loc)
{
    switch (level)
    {
        case LogLevel::None:
			std::cout << Color::White << "        " << message << Color::Reset << "\n";
            break;

        case LogLevel::Info:
            std::cout << Color::White << "[INFO]  " << Color::Reset << message << "\n";
            break;

        case LogLevel::Success:
            std::cout << Color::BoldGreen << "[OK]    " << Color::Reset << message << "\n";
            break;

        case LogLevel::Warning:
            std::cerr << Color::BoldYellow << "[WARN]  " << Color::Reset << message << "\n";
            break;

        case LogLevel::Error:
            std::cerr << Color::BoldRed << "[ERROR] " << Color::Reset
                << Color::Red << message << Color::Reset
                << "\n"
                << Color::Red << "        at " << loc.file_name()
                << ":" << loc.line() << Color::Reset << "\n";
            break;

        case LogLevel::Vulkan:
            std::cerr << Color::BoldMagenta << "[VK]\t" << Color::Reset << Color::Magenta << message << Color::Reset << "\n";
            break;

        case LogLevel::Section:
            std::cout << "\n" << Color::BoldCyan
                << "========================================\n"
                << "" << message << "\n"
                << "========================================"
                << Color::Reset << "\n\n";
            break;
    }
}


void Logger::Log(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::None, msg, loc);
}

void Logger::Info(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::Info, msg, loc);
}

void Logger::Success(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::Success, msg, loc);
}

void Logger::Warn(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::Warning, msg, loc);
}

void Logger::Error(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::Error, msg, loc);
}

void Logger::Vulkan(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::Vulkan, msg, loc);
}

void Logger::Section(const std::string_view& msg, const std::source_location loc)
{
    Log(LogLevel::Section, msg, loc);
}
