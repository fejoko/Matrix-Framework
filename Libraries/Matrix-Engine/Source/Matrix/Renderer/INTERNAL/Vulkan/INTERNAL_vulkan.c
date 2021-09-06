#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan.h"

#include "Matrix/Application/application_data.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_errors.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_helpers.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window_data.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window_errors.h"

#include "Stb/stb_sprintf.h"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#ifdef ___MTRX_DEBUG
#define MTRX_VULKAN_ENABLED_INSTANCE_LAYERS "VK_LAYER_KHRONOS_validation"
#define MTRX_VULKAN_ENABLED_INSTANCE_LAYERS_COUNT 1
#define MTRX_VULKAN_ENABLED_DEVICE_LAYERS ""
#define MTRX_VULKAN_ENABLED_DEVICE_LAYERS_COUNT 0
#else
#define MTRX_VULKAN_ENABLED_INSTANCE_LAYERS ""
#define MTRX_VULKAN_ENABLED_INSTANCE_LAYERS_COUNT 0
#define MTRX_VULKAN_ENABLED_DEVICE_LAYERS ""
#define MTRX_VULKAN_ENABLED_DEVICE_LAYERS_COUNT 0
#endif // ___MTRX_DEBUG

void matrix_vulkan_construct(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		renderer->api_data = NULL;
		renderer->api_data = malloc(sizeof(Matrix_Vulkan_Data));
		if (NULL == renderer->api_data)
		{
			MTRX_ERROR_MALLOC_FAILED;
		}
		else
		{

		}
	}
}

void matrix_vulkan_init(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == (renderer->api_data))
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			matrix_vulkan_create_instance(renderer->api_data, renderer);
			matrix_vulkan_enumerate_physical_devices(renderer->api_data, renderer);
			matrix_vulkan_create_device(renderer->api_data, renderer);
		}
	}
}

void matrix_vulkan_start(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_vulkan_create_surface(renderer->api_data, renderer);
		matrix_vulkan_create_swapchain(renderer->api_data, renderer);
		matrix_vulkan_create_imageviews(renderer->api_data, renderer);
	}
}

void matrix_vulkan_update(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{

	}
}

void matrix_vulkan_stop(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_vulkan_destroy_imageviews(renderer->api_data, renderer);
		matrix_vulkan_destroy_swapchain(renderer->api_data, renderer);
		matrix_vulkan_destroy_surface(renderer->api_data, renderer);
	}
}

void matrix_vulkan_shutdown(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		vkDeviceWaitIdle(((Matrix_Vulkan_Data*)renderer->api_data)->device);

		matrix_vulkan_destroy_device(renderer->api_data, renderer);
		matrix_vulkan_denumerate_physical_devices(renderer->api_data, renderer);
		matrix_vulkan_destroy_instance(renderer->api_data, renderer);
	}
}

void matrix_vulkan_destruct(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		free(renderer->api_data);
	}
}

void matrix_vulkan_create_instance(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			MTRX_CORE_LOG("renderer: instance creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			VkApplicationInfo application_info;
			application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			application_info.pNext = NULL;
			application_info.pApplicationName = renderer->application->application_info.application_name;
			application_info.applicationVersion = renderer->application->application_info.application_version;
			application_info.pEngineName = renderer->engine->engine_info.ENGINE_NAME;
			application_info.engineVersion = renderer->engine->engine_info.ENGINE_VERSION;
			application_info.apiVersion = VK_API_VERSION_1_2;

			uint32_t enabled_layers_count = MTRX_VULKAN_ENABLED_INSTANCE_LAYERS_COUNT;
			const char* enabled_layers[] = { MTRX_VULKAN_ENABLED_INSTANCE_LAYERS };

			uint32_t enabled_extentions_count = 0;
			const char** enabled_extentions = "";

			if (NULL == renderer->window)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				switch (matrix_window_api_get(renderer->window))
				{
				case MATRIX_WINDOW_API_NONE:
					MTRX_CORE_LOG("renderer: window is using vulkan incompatible api", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
					break;
				case MATRIX_WINDOW_API_GLFW:
					enabled_extentions = glfwGetRequiredInstanceExtensions(&enabled_extentions_count);
					break;
				case MATRIX_WINDOW_API_WINDOWS:
					break;
				default:
					MTRX_ERROR_WINDOW_API_OUTOFBOUND;
					break;
				}

				VkInstanceCreateInfo instance_create_info;
				instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				instance_create_info.pNext = NULL;
				instance_create_info.flags = 0;
				instance_create_info.pApplicationInfo = &application_info;
				instance_create_info.enabledLayerCount = enabled_layers_count;
				instance_create_info.ppEnabledLayerNames = enabled_layers;
				instance_create_info.enabledExtensionCount = enabled_extentions_count;
				instance_create_info.ppEnabledExtensionNames = enabled_extentions;

				VkResult result = vkCreateInstance(&instance_create_info, NULL, &api_data->instance);
				matrix_vulkan_assert_result("vkCreateInstance", result, renderer);
			}
		}
	}
}

void matrix_vulkan_enumerate_physical_devices(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			MTRX_CORE_LOG("renderer: physical_device enumeration", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			api_data->physical_device_count = 0;
			VkResult result = vkEnumeratePhysicalDevices(api_data->instance, &api_data->physical_device_count, NULL);
			matrix_vulkan_assert_result("vkEnumeratePhysicalDevices (1/2)", result, renderer);
			api_data->physical_device_all = NULL;
			api_data->physical_device_all = malloc(sizeof(*api_data->physical_device_all) * api_data->physical_device_count);
			if (NULL == api_data->physical_device_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				result = vkEnumeratePhysicalDevices(api_data->instance, &api_data->physical_device_count, api_data->physical_device_all);
				matrix_vulkan_assert_result("vkEnumeratePhysicalDevices (2/2)", result, renderer);

				api_data->physical_device_all_properties = NULL;
				api_data->physical_device_all_properties = malloc(sizeof(*api_data->physical_device_all_properties) * api_data->physical_device_count);
				if (NULL == api_data->physical_device_all_properties)
				{
					MTRX_ERROR_UNEXPECTED_NULL;
				}
				else
				{
					api_data->physical_device_all_features = NULL;
					api_data->physical_device_all_features = malloc(sizeof(*api_data->physical_device_all_features) * api_data->physical_device_count);
					if (NULL == api_data->physical_device_all_features)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						api_data->physical_device_all_memory_properties = NULL;
						api_data->physical_device_all_memory_properties = malloc(sizeof(*api_data->physical_device_all_memory_properties) * api_data->physical_device_count);
						if (NULL == api_data->physical_device_all_memory_properties)
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							for (uint32_t i = 0; i < api_data->physical_device_count; i++)
							{
								vkGetPhysicalDeviceProperties(api_data->physical_device_all[i], &api_data->physical_device_all_properties[i]);
								vkGetPhysicalDeviceFeatures(api_data->physical_device_all[i], &api_data->physical_device_all_features[i]);
								vkGetPhysicalDeviceMemoryProperties(api_data->physical_device_all[i], &api_data->physical_device_all_memory_properties[i]);
							}

							api_data->physical_device_used_index = 0; //@TODO: pick best physical_device
						}
					}
				}
			}
		}
	}
}

void matrix_vulkan_create_device(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			MTRX_CORE_LOG("renderer: device creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			api_data->queue_family_count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(api_data->physical_device_all[api_data->physical_device_used_index], &api_data->queue_family_count, NULL);
			api_data->queue_family_properties = NULL;
			api_data->queue_family_properties = malloc(sizeof(*api_data->queue_family_properties) * api_data->queue_family_count);
			if (api_data->queue_family_properties == NULL)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				vkGetPhysicalDeviceQueueFamilyProperties(api_data->physical_device_all[api_data->physical_device_used_index], &api_data->queue_family_count, api_data->queue_family_properties);

				const float queue_priorities[] = { 1.0f };
				
				VkDeviceQueueCreateInfo device_queue_create_info;
				device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				device_queue_create_info.pNext = NULL;
				device_queue_create_info.flags = 0;
				device_queue_create_info.queueFamilyIndex = 0;//@TODO
				device_queue_create_info.queueCount = 1;//@TODO
				device_queue_create_info.pQueuePriorities = &queue_priorities;
				
				uint32_t enabled_layers_count = MTRX_VULKAN_ENABLED_DEVICE_LAYERS_COUNT;
				const char* enabled_layers[] = { MTRX_VULKAN_ENABLED_DEVICE_LAYERS };
				
				uint32_t enabled_extentions_count = 1;
				const char* enabled_extentions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
				
				VkPhysicalDeviceFeatures enabled_physical_device_features = { VK_FALSE };
				
				VkDeviceCreateInfo device_create_info;
				device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				device_create_info.pNext = NULL;
				device_create_info.flags = 0;
				device_create_info.queueCreateInfoCount = 1;
				device_create_info.pQueueCreateInfos = &device_queue_create_info;
				device_create_info.enabledLayerCount = enabled_layers_count;
				device_create_info.ppEnabledLayerNames = enabled_layers;
				device_create_info.enabledExtensionCount = enabled_extentions_count;
				device_create_info.ppEnabledExtensionNames = enabled_extentions;
				device_create_info.pEnabledFeatures = &enabled_physical_device_features;
				
				VkResult result = vkCreateDevice(api_data->physical_device_all[api_data->physical_device_used_index], &device_create_info, NULL, &api_data->device);
				matrix_vulkan_assert_result("vkCreateDevice", result, renderer);
				
				vkGetDeviceQueue(api_data->device, 0, 0, &api_data->queue); //@TODO
			}
		}
	}
}

void matrix_vulkan_create_surface(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			MTRX_CORE_LOG("renderer: surface creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			if (NULL == renderer->window)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				if (matrix_window_opened_is(renderer->window))
				{
					VkResult result;

					switch (matrix_window_api_get(renderer->window))
					{
					case MATRIX_WINDOW_API_NONE:
						MTRX_CORE_LOG("renderer: window is using vulkan incompatible api", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
						break;
					case MATRIX_WINDOW_API_GLFW:
						result = glfwCreateWindowSurface(api_data->instance, matrix_window_raw_get(renderer->window), NULL, &api_data->surface);
						matrix_vulkan_assert_result("glfwCreateWindowSurface", result, renderer);

						api_data->surface_support_is = VK_FALSE;
						VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(api_data->physical_device_all[api_data->physical_device_used_index], 0, api_data->surface, &api_data->surface_support_is);
						matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfaceSupportKHR", result, renderer);
						if (VK_TRUE == api_data->surface_support_is)
						{
							result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->surface_capabilities);
							matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", result, renderer);

							api_data->surface_format_count = 0;
							result = vkGetPhysicalDeviceSurfaceFormatsKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->surface_format_count, NULL);
							matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfaceFormatsKHR (1/2)", result, renderer);
							api_data->surface_format_all = NULL;
							api_data->surface_format_all = malloc(sizeof(*api_data->surface_format_all) * api_data->surface_format_count);
							if (NULL == api_data->surface_format_all)
							{
								MTRX_ERROR_UNEXPECTED_NULL;
							}
							else
							{
								result = vkGetPhysicalDeviceSurfaceFormatsKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->surface_format_count, api_data->surface_format_all);
								matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfaceFormatsKHR (2/2)", result, renderer);

								api_data->present_mode_count = 0;
								result = vkGetPhysicalDeviceSurfacePresentModesKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->present_mode_count, NULL);
								matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfacePresentModesKHR (1/2)", result, renderer);
								api_data->present_mode_all = NULL;
								api_data->present_mode_all = malloc(sizeof(*api_data->present_mode_all) * api_data->present_mode_count);
								if (NULL == api_data->present_mode_all)
								{
									MTRX_ERROR_UNEXPECTED_NULL;
								}
								else
								{
									result = vkGetPhysicalDeviceSurfacePresentModesKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->present_mode_count, api_data->present_mode_all);
									matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfacePresentModesKHR (2/2)", result, renderer);
								}
							}
						}
						else
						{
							MTRX_CORE_LOG("renderer: surface not supported", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
						}
						break;
					case MATRIX_WINDOW_API_WINDOWS:
						break;
					default:
						MTRX_ERROR_WINDOW_API_OUTOFBOUND;
						break;
					}
				}
				else
				{
					MTRX_CORE_LOG("renderer: could not create surface -> window is closed", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
				}
			}
		}
	}
}

void matrix_vulkan_create_swapchain(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			MTRX_CORE_LOG("renderer: swapchain creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			VkSwapchainCreateInfoKHR swapchain_create_info;
			swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			swapchain_create_info.pNext = NULL;
			swapchain_create_info.flags = 0;
			swapchain_create_info.surface = api_data->surface;
			swapchain_create_info.minImageCount = 1; //@TODO
			swapchain_create_info.imageFormat = VK_FORMAT_B8G8R8A8_UNORM; //@TODO
			swapchain_create_info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; //@TODO

			if (NULL == renderer->window)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				if (matrix_window_opened_is(renderer->window))
				{
					swapchain_create_info.imageExtent.width = matrix_window_width_get(renderer->window);
					swapchain_create_info.imageExtent.height = matrix_window_height_get(renderer->window);

					swapchain_create_info.imageArrayLayers = 1;
					swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //@TODO
					swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; //@TODO
					swapchain_create_info.queueFamilyIndexCount = 0; //@TODO
					swapchain_create_info.pQueueFamilyIndices = NULL; //@TODO
					swapchain_create_info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
					swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
					swapchain_create_info.presentMode = VK_PRESENT_MODE_FIFO_KHR; //@TODO -> better one available?
					swapchain_create_info.clipped = VK_TRUE;
					swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;

					VkResult result = vkCreateSwapchainKHR(api_data->device, &swapchain_create_info, NULL, &api_data->swapchain);
					matrix_vulkan_assert_result("vkCreateSwapchainKHR", result, renderer);

					api_data->swapchain_image_count = 0;
					result = vkGetSwapchainImagesKHR(api_data->device, api_data->swapchain, &api_data->swapchain_image_count, NULL);
					matrix_vulkan_assert_result("vkGetSwapchainImagesKHR (1/2)", result, renderer);
					api_data->swapchain_image_all = NULL;
					api_data->swapchain_image_all = malloc(sizeof(*api_data->swapchain_image_all) * api_data->swapchain_image_count);
					if (NULL == api_data->swapchain_image_all)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						result = vkGetSwapchainImagesKHR(api_data->device, api_data->swapchain, &api_data->swapchain_image_count, &api_data->swapchain_image_all);
						matrix_vulkan_assert_result("vkGetSwapchainImagesKHR (2/2)", result, renderer);
					}
				}
				else
				{
					MTRX_CORE_LOG("renderer: could not create swapchain -> window is closed", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
				}
			}
		}
	}
}

void matrix_vulkan_create_imageviews(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			MTRX_CORE_LOG("renderer: imageview creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			VkImageViewCreateInfo image_view_create_info;
			image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			image_view_create_info.pNext = NULL;
			image_view_create_info.flags = 0;
			image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			image_view_create_info.format = VK_FORMAT_B8G8R8A8_UNORM; //@TODO;
			image_view_create_info.components.r = VK_COMPONENT_SWIZZLE_R;
			image_view_create_info.components.g = VK_COMPONENT_SWIZZLE_G;
			image_view_create_info.components.b = VK_COMPONENT_SWIZZLE_B;
			image_view_create_info.components.a = VK_COMPONENT_SWIZZLE_A;
			image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			image_view_create_info.subresourceRange.baseMipLevel = 0;
			image_view_create_info.subresourceRange.levelCount = 1;
			image_view_create_info.subresourceRange.baseArrayLayer = 0;
			image_view_create_info.subresourceRange.layerCount = 1;

			api_data->image_view_all = NULL;
			api_data->image_view_all = malloc(sizeof(*api_data->image_view_all) * api_data->swapchain_image_count);
			if (NULL == api_data->image_view_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				for (uint32_t i = 0; i < api_data->swapchain_image_count; i++)
				{
					image_view_create_info.image = &api_data->swapchain_image_all[i];

					VkResult result = vkCreateImageView(api_data->device, &image_view_create_info, NULL, &api_data->image_view_all[i]);
					int decimals = 1;
					for (int w = i + 1; w >= 10; w /= 10)
					{
						decimals++;
					}
					char* message = NULL;
					message = malloc(sizeof(*message) * (21 + decimals));
					stbsp_sprintf(message, "vkCreateImageView (%u)", i + 1);
					matrix_vulkan_assert_result(message, result, renderer);
				}
			}
		}
	}
}

void matrix_vulkan_create_shaders(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_create_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_destroy_surface(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			if (NULL == renderer->window)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				switch (matrix_window_api_get(renderer->window))
				{
				case MATRIX_WINDOW_API_NONE:
					MTRX_CORE_LOG("renderer: window is using vulkan incompatible api", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
					break;
				case MATRIX_WINDOW_API_GLFW:
					if (NULL == api_data->surface_format_all)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						if (NULL == api_data->present_mode_all)
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							free(api_data->present_mode_all);
							free(api_data->surface_format_all);

							MTRX_CORE_LOG("renderer: surface destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
						}
					}

					vkDestroySurfaceKHR(api_data->instance, api_data->surface, NULL);
					break;
				case MATRIX_WINDOW_API_WINDOWS:
					break;
				default:
					MTRX_ERROR_WINDOW_API_OUTOFBOUND;
					break;
				}
			}
		}
	}
}

void matrix_vulkan_destroy_swapchain(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			vkDestroySwapchainKHR(api_data->device, api_data->swapchain, NULL);

			MTRX_CORE_LOG("renderer: swapchain destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
}

void matrix_vulkan_destroy_imageviews(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			for (uint32_t i = 0; i < api_data->swapchain_image_count; i++)
			{
				vkDestroyImageView(api_data->device, api_data->image_view_all[i], NULL);
			}

			free(api_data->image_view_all);

			MTRX_CORE_LOG("renderer: swapchain destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
}

void matrix_vulkan_destroy_shaders(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_destroy_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_destroy_instance(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			vkDestroyInstance(api_data->instance, NULL);

			MTRX_CORE_LOG("renderer: instance destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
}

void matrix_vulkan_denumerate_physical_devices(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			if (NULL == api_data->physical_device_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				if (NULL == api_data->physical_device_all_properties)
				{
					MTRX_ERROR_UNEXPECTED_NULL;
				}
				else
				{
					if (NULL == api_data->physical_device_all_features)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						if (NULL == api_data->physical_device_all_memory_properties)
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							free(api_data->physical_device_all_memory_properties);
							free(api_data->physical_device_all_features);
							free(api_data->physical_device_all_properties);
							free(api_data->physical_device_all);

							MTRX_CORE_LOG("renderer: physical_device denumeration", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
						}
					}
				}
			}
		}
	}
}

void matrix_vulkan_destroy_device(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == api_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			if (api_data->queue_family_properties == NULL)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				free(api_data->queue_family_properties);

				vkDestroyDevice(api_data->device, NULL);

				MTRX_CORE_LOG("renderer: device destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
			}
		}
	}
}