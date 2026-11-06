#include "VulkanException.h"


VulkanException::VulkanException(const std::string& message, const std::source_location loc)
    : m_Message(message), m_Location(loc)
{
    Logger::Error(message, loc);
}


const char* VulkanException::what() const noexcept
{
    return m_Message.c_str();
}

const std::source_location& VulkanException::where() const noexcept
{
    return m_Location;
}
