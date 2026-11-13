#include "pch.h"
#include "VulkanApp.h"


namespace VulkanRenderer
{
	VulkanApp::VulkanApp(std::string_view appName, std::string_view engineName, glm::uvec2 windowSize)
		: m_WindowSize(windowSize)
		, m_AppName(appName)
		, m_EngineName(engineName)
		, mp_Window(nullptr)
		, m_Instance(nullptr)
	{}


	void VulkanApp::Init()
	{
		Logger::Section("Initializing Window");
		CreateWindow();

		Logger::Section("Initializing Vulkan");
		InitVulkan();
	}

	void VulkanApp::Run()
	{
		Logger::Section("Entering Main Loop");
		MainLoop();
	}

	void VulkanApp::Cleanup()
	{

	}


	void VulkanApp::CreateWindow()
	{
		if (!glfwInit())
			throw VulkanException("Unable to initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		mp_Window = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, m_AppName.data(), nullptr, nullptr);
		if (mp_Window == nullptr)
			throw VulkanException("Failed to create GLFW window");

		glfwSetWindowUserPointer(mp_Window, this);

		mp_Monitors = GetMonitors();
		if (mp_Monitors.size() <= 0)
			throw VulkanException("No monitors found");
		MoveWindowToMonitor(mp_Monitors.front());

		Logger::Success("GLFW window created (" + std::to_string(m_WindowSize.x) + "x" + std::to_string(m_WindowSize.y) + ")");
	}

	std::span<GLFWmonitor*> VulkanApp::GetMonitors()
	{
		std::int32_t monitorCount;
		GLFWmonitor** monitorPointers = glfwGetMonitors(&monitorCount);
		return std::span<GLFWmonitor*>{monitorPointers, static_cast<std::size_t>(monitorCount)};
	}

	void VulkanApp::MoveWindowToMonitor(GLFWmonitor* monitor)
	{
		glm::uvec2 monitorPosition{};
		glfwGetMonitorPos(monitor, (int*)&monitorPosition.x, (int*)&monitorPosition.y);

		glm::uvec2 monitorSize{};
		glfwGetMonitorWorkarea(monitor, nullptr, nullptr, (int*)&monitorSize.x, (int*)&monitorSize.y);

		const glm::uvec2 newWindowPosition =  + (monitorSize / 2U) - (m_WindowSize / 2U);
		glfwSetWindowPos(mp_Window, newWindowPosition.x, newWindowPosition.y);
	}


	void VulkanApp::InitVulkan()
	{
		CreateInstance();
	}

	void VulkanApp::CreateInstance()
	{
		if (kb_EnableValidation)
			CheckValidationLayerSupport();

		vk::ApplicationInfo appInfo{};
		appInfo.pApplicationName	= m_AppName.data();
		appInfo.applicationVersion	= VK_MAKE_VERSION(0, 1, 0);
		appInfo.pEngineName			= m_EngineName.data();
		appInfo.engineVersion		= VK_MAKE_VERSION(0, 1, 0);
		appInfo.apiVersion			= VK_API_VERSION_1_4;

		std::vector<const char*> extensions = GetRequiredExtensions();

		vk::InstanceCreateInfo createInfo{};
		createInfo.pApplicationInfo			= &appInfo;
		createInfo.enabledLayerCount		= kb_EnableValidation ? static_cast<std::uint32_t>(k_ValidationLayers.size()) : 0U;
		createInfo.ppEnabledLayerNames		= kb_EnableValidation ? k_ValidationLayers.data() : nullptr;
		createInfo.enabledExtensionCount	= static_cast<std::uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames	= extensions.data();

		m_Instance = vk::raii::Instance(m_Context, createInfo);

		Logger::Success("vk::Instance created");
		if (kb_EnableValidation)
			Logger::Info("Validation layers active");

		PrintAvailableExtensions();
	}


	void VulkanApp::CheckValidationLayerSupport()
	{
		const auto availableLayers = vk::enumerateInstanceLayerProperties();

		for (const std::string_view requested : k_ValidationLayers)
		{
			const bool found = std::ranges::any_of
			(
				availableLayers,
				[requested](const vk::LayerProperties& layer)
				{ return requested == std::string_view{ layer.layerName }; }
			);

			if (!found)
			{
				std::string message = "Validation layer not found: ";
				message.append(requested);
				throw VulkanException(std::move(message));
			}
		}
	}

	std::vector<const char*> VulkanApp::GetRequiredExtensions()
	{
		std::uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions;
		extensions.reserve(glfwExtensionCount);

		for (std::uint32_t i = 0; i < glfwExtensionCount; ++i)
			extensions.emplace_back(glfwExtensions[i]);

		if (kb_EnableValidation)
			extensions.emplace_back(vk::EXTDebugUtilsExtensionName);

		return extensions;
	}

	void VulkanApp::PrintAvailableExtensions()
	{
		auto extensions = vk::enumerateInstanceExtensionProperties();
		Logger::Info("Available Vulkan instance extensions (" + std::to_string(extensions.size()) + "):");
		for (const auto& ext : extensions)
			Logger::Log(std::string("    ") + ext.extensionName.data());
	}


	void VulkanApp::MainLoop()
	{
		while (!glfwWindowShouldClose(mp_Window))
		{
			glfwPollEvents();
		}
	}
}
