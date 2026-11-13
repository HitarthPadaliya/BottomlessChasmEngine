#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include "pch.h"
#include "VulkanApp.h"


int main()
{
	try
	{
		VulkanRenderer::VulkanApp app;
		app.Run();
	}
	catch (const VulkanException&)
	{
		return EXIT_FAILURE;
	}
	catch (const vk::SystemError& e)
	{
		Logger::Error(std::string("Vulkan system error: ") + e.what());
		return EXIT_FAILURE;
	}
	catch (const std::exception& e)
	{
		Logger::Error(std::string("Unhandled exception: ") + e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
