#pragma once

#include "pch.h"
#include "Logger.h"


class VulkanException : public std::exception
{
    private:
        std::string_view m_Message;
        std::source_location m_Location;


    public:
        explicit VulkanException(const std::string_view& message, const std::source_location loc = std::source_location::current());
        
        const char* what() const noexcept override;
        const std::source_location& where() const noexcept;
};
