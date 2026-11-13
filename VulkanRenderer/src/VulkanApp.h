#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_raii.hpp>

#include "pch.h"
#include "Logger.h"
#include "VulkanException.h"


#ifdef NDEBUG
	constexpr bool kb_EnableValidation = true;
#else
	constexpr bool kb_EnableValidation = false;
#endif

constexpr std::array<const char*, 1> k_ValidationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

constexpr std::array<const char*, 1> k_DeviceExtensions =
{
	vk::KHRSwapchainExtensionName
};


namespace VulkanRenderer
{
	class VulkanApp final
	{
		private:
			glm::uvec2 m_WindowSize;
			std::string m_AppName;
			std::string m_EngineName;

			GLFWwindow* mp_Window;
			std::span<GLFWmonitor*> mp_Monitors;

			vk::raii::Context m_Context;
			vk::raii::Instance m_Instance;


		public:
			VulkanApp(std::string_view appName = "Descent", std::string_view engineName = "BottomlessChasm", glm::uvec2 windowSize = {1280, 720});

			void Init();
			void Run();
			void Cleanup();


		private:
			void CreateWindow();
			std::span<GLFWmonitor*> GetMonitors();
			void MoveWindowToMonitor(GLFWmonitor* monitor);

			void InitVulkan();
			void CreateInstance();

			void CheckValidationLayerSupport();
			std::vector<const char*> GetRequiredExtensions();
			void PrintAvailableExtensions();

			void MainLoop();

	};
}
