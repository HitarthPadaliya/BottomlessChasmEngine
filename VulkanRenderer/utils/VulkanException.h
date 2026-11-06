#pragma once

#include <iostream>
#include <source_location>

#include "Logger.h"


class VulkanException : public std::exception
{
    private:
        std::string m_Message;
        std::source_location m_Location;


    public:
        explicit VulkanException(const std::string& message, const std::source_location loc = std::source_location::current());
        
        const char* what() const noexcept override;
        const std::source_location& where() const noexcept;
};
