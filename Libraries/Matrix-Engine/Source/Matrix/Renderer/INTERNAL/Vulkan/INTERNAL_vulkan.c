#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan.h"

#include "Matrix/Application/application_data.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_errors.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_errors.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_helpers.h"
#include "Matrix/Vector/vector.h"
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
		matrix_vulkan_create_shader(renderer->api_data, renderer);
		matrix_vulkan_create_pipeline(renderer->api_data, renderer);
		matrix_vulkan_create_frame_buffer(renderer->api_data, renderer);
		matrix_vulkan_create_command_buffer(renderer->api_data, renderer);
		matrix_vulkan_create_semaphore(renderer->api_data, renderer);
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
		matrix_vulkan_frame_draw(renderer->api_data, renderer);
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
		vkDeviceWaitIdle(((Matrix_Vulkan_Data*)renderer->api_data)->device);

		matrix_vulkan_destroy_semaphore(renderer->api_data, renderer);
		matrix_vulkan_destroy_command_buffer(renderer->api_data, renderer);
		matrix_vulkan_destroy_frame_buffer(renderer->api_data, renderer);
		matrix_vulkan_destroy_pipeline(renderer->api_data, renderer);
		matrix_vulkan_destroy_shaders(renderer->api_data, renderer);
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
			const char** enabled_extentions = NULL;

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
				MTRX_VULKAN_ASSERT("vkCreateInstance", result, renderer);
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
			MTRX_VULKAN_ASSERT("vkEnumeratePhysicalDevices (1/2)", result, renderer);
			api_data->physical_device_all = NULL;
			api_data->physical_device_all = malloc(sizeof(*api_data->physical_device_all) * api_data->physical_device_count);
			if (NULL == api_data->physical_device_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				result = vkEnumeratePhysicalDevices(api_data->instance, &api_data->physical_device_count, api_data->physical_device_all);
				MTRX_VULKAN_ASSERT("vkEnumeratePhysicalDevices (2/2)", result, renderer);

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
				device_queue_create_info.pQueuePriorities = queue_priorities;
				
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
				MTRX_VULKAN_ASSERT("vkCreateDevice", result, renderer);
				
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
						MTRX_VULKAN_ASSERT("glfwCreateWindowSurface", result, renderer);

						api_data->surface_support_is = VK_FALSE;
						VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(api_data->physical_device_all[api_data->physical_device_used_index], 0, api_data->surface, &api_data->surface_support_is);
						MTRX_VULKAN_ASSERT("vkGetPhysicalDeviceSurfaceSupportKHR", result, renderer);
						if (VK_TRUE == api_data->surface_support_is)
						{
							result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->surface_capabilities);
							MTRX_VULKAN_ASSERT("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", result, renderer);

							api_data->surface_format_count = 0;
							result = vkGetPhysicalDeviceSurfaceFormatsKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->surface_format_count, NULL);
							MTRX_VULKAN_ASSERT("vkGetPhysicalDeviceSurfaceFormatsKHR (1/2)", result, renderer);
							api_data->surface_format_all = NULL;
							api_data->surface_format_all = malloc(sizeof(*api_data->surface_format_all) * api_data->surface_format_count);
							if (NULL == api_data->surface_format_all)
							{
								MTRX_ERROR_UNEXPECTED_NULL;
							}
							else
							{
								result = vkGetPhysicalDeviceSurfaceFormatsKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->surface_format_count, api_data->surface_format_all);
								MTRX_VULKAN_ASSERT("vkGetPhysicalDeviceSurfaceFormatsKHR (2/2)", result, renderer);

								api_data->present_mode_count = 0;
								result = vkGetPhysicalDeviceSurfacePresentModesKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->present_mode_count, NULL);
								MTRX_VULKAN_ASSERT("vkGetPhysicalDeviceSurfacePresentModesKHR (1/2)", result, renderer);
								api_data->present_mode_all = NULL;
								api_data->present_mode_all = malloc(sizeof(*api_data->present_mode_all) * api_data->present_mode_count);
								if (NULL == api_data->present_mode_all)
								{
									MTRX_ERROR_UNEXPECTED_NULL;
								}
								else
								{
									result = vkGetPhysicalDeviceSurfacePresentModesKHR(api_data->physical_device_all[api_data->physical_device_used_index], api_data->surface, &api_data->present_mode_count, api_data->present_mode_all);
									MTRX_VULKAN_ASSERT("vkGetPhysicalDeviceSurfacePresentModesKHR (2/2)", result, renderer);
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

			api_data->format_used = VK_FORMAT_B8G8R8A8_UNORM; //@TODO

			VkSwapchainCreateInfoKHR swapchain_create_info;
			swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			swapchain_create_info.pNext = NULL;
			swapchain_create_info.flags = 0;
			swapchain_create_info.surface = api_data->surface;
			swapchain_create_info.minImageCount = 1; //@TODO //@CHANGE
			swapchain_create_info.imageFormat = api_data->format_used;
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
					MTRX_VULKAN_ASSERT("vkCreateSwapchainKHR", result, renderer);

					api_data->swapchain_image_count = 0;
					result = vkGetSwapchainImagesKHR(api_data->device, api_data->swapchain, &api_data->swapchain_image_count, NULL);
					MTRX_VULKAN_ASSERT("vkGetSwapchainImagesKHR (1/2)", result, renderer);
					api_data->swapchain_image_all = NULL;
					api_data->swapchain_image_all = malloc(sizeof(*api_data->swapchain_image_all) * api_data->swapchain_image_count);
					if (NULL == api_data->swapchain_image_all)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						result = vkGetSwapchainImagesKHR(api_data->device, api_data->swapchain, &api_data->swapchain_image_count, api_data->swapchain_image_all);
						MTRX_VULKAN_ASSERT("vkGetSwapchainImagesKHR (2/2)", result, renderer);
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
			image_view_create_info.format = api_data->format_used;
			image_view_create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			image_view_create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			image_view_create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			image_view_create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
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
					image_view_create_info.image = api_data->swapchain_image_all[i];
					
					VkResult result = vkCreateImageView(api_data->device, &image_view_create_info, NULL, &api_data->image_view_all[i]);
					int decimals = 1;
					for (int w = i + 1; w >= 10; w /= 10)
					{
						decimals++;
					}
					char* message = NULL;
					message = malloc(sizeof(*message) * (21 + decimals));
					stbsp_sprintf(message, "vkCreateImageView (%u)", i + 1);
					MTRX_VULKAN_ASSERT(message, result, renderer);
					free(message);
				}
			}
		}
	}
}

void matrix_vulkan_create_shader(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			MTRX_CORE_LOG("renderer: shader creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			api_data->shader_module_all = NULL;
			api_data->shader_module_all = malloc(sizeof(*api_data->shader_module_all) * matrix_vector_capacity(renderer->shader_vec));
			if (NULL == api_data->shader_module_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				VkShaderModuleCreateInfo shader_module_create_info;
				shader_module_create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				shader_module_create_info.pNext = NULL;
				shader_module_create_info.flags = 0;

				for (size_t i = 0; i < matrix_vector_capacity(renderer->shader_vec); i++)
				{
					shader_module_create_info.codeSize = MTRX_VECTOR_AT_AS(Matrix_Renderer_Shader, i, renderer->shader_vec).shader_size;
					shader_module_create_info.pCode = (const uint32_t*)MTRX_VECTOR_AT_AS(Matrix_Renderer_Shader, i, renderer->shader_vec).shader_data;

					VkResult result = vkCreateShaderModule(api_data->device, &shader_module_create_info, NULL, &api_data->shader_module_all[i]);
					int decimals = 1;
					for (int w = i + 1; w >= 10; w /= 10)
					{
						decimals++;
					}
					char* message = NULL;
					message = malloc(sizeof(*message) * (25 + decimals));
					stbsp_sprintf(message, "vkCreateShaderModule (%lu)", i + 1);
					MTRX_VULKAN_ASSERT(message, result, renderer);
					free(message);
				}
			}
		}
	}
}

void matrix_vulkan_create_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			MTRX_CORE_LOG("renderer: pipeline creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			Matrix_Vector* pipeline_shader_stage_create_info_vec = matrix_vector_construct(sizeof(VkPipelineShaderStageCreateInfo), matrix_vector_capacity(renderer->shader_vec));

			for (size_t i = 0; i < matrix_vector_capacity(pipeline_shader_stage_create_info_vec); i++)
			{
				VkPipelineShaderStageCreateInfo pipeline_shader_stage_create_info;
				pipeline_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				pipeline_shader_stage_create_info.pNext = NULL;
				pipeline_shader_stage_create_info.flags = 0;
				switch (MTRX_VECTOR_AT_AS(Matrix_Renderer_Shader, i, renderer->shader_vec).shader_type)
				{
				case MATRIX_RENDERER_SHADER_TYPE_VERTEX:
					pipeline_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
					break;
				case MATRIX_RENDERER_SHADER_TYPE_FRAGMENT:
					pipeline_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
					break;
				default:
					MTRX_ERROR_RENDERER_SHADER_TYPE_OUTOFBOUND;
					break;
				}
				pipeline_shader_stage_create_info.module = api_data->shader_module_all[i];
				pipeline_shader_stage_create_info.pName = "main";
				pipeline_shader_stage_create_info.pSpecializationInfo = NULL;

				MTRX_VECTOR_AT_AS(VkPipelineShaderStageCreateInfo, i, pipeline_shader_stage_create_info_vec) = pipeline_shader_stage_create_info;
			}

			VkPipelineVertexInputStateCreateInfo pipeline_vertex_input_state_create_info;
			pipeline_vertex_input_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			pipeline_vertex_input_state_create_info.pNext = NULL;
			pipeline_vertex_input_state_create_info.flags = 0;
			pipeline_vertex_input_state_create_info.vertexBindingDescriptionCount = 0;
			pipeline_vertex_input_state_create_info.pVertexBindingDescriptions = NULL;
			pipeline_vertex_input_state_create_info.vertexAttributeDescriptionCount = 0;
			pipeline_vertex_input_state_create_info.pVertexAttributeDescriptions = NULL;

			VkPipelineInputAssemblyStateCreateInfo pipelien_input_assembly_state_create_info;
			pipelien_input_assembly_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			pipelien_input_assembly_state_create_info.pNext = NULL;
			pipelien_input_assembly_state_create_info.flags = 0;
			pipelien_input_assembly_state_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			pipelien_input_assembly_state_create_info.primitiveRestartEnable = VK_FALSE;

			if (NULL == renderer->window)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				if (matrix_window_opened_is(renderer->window))
				{
					VkViewport viewport;
					viewport.x = 0.0f;
					viewport.y = 0.0f;
					viewport.width = matrix_window_width_get(renderer->window);
					viewport.height = matrix_window_height_get(renderer->window);
					viewport.minDepth = 0.0f;
					viewport.maxDepth = 1.0f;

					VkRect2D scissor;
					scissor.offset.x = 0;
					scissor.offset.y = 0;
					scissor.extent.width = matrix_window_width_get(renderer->window);
					scissor.extent.height = matrix_window_height_get(renderer->window);

					VkPipelineViewportStateCreateInfo pipeline_viewport_state_create_info;
					pipeline_viewport_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
					pipeline_viewport_state_create_info.pNext = NULL;
					pipeline_viewport_state_create_info.flags = 0;
					pipeline_viewport_state_create_info.viewportCount = 1;
					pipeline_viewport_state_create_info.pViewports = &viewport;
					pipeline_viewport_state_create_info.scissorCount = 1;
					pipeline_viewport_state_create_info.pScissors = &scissor;

					VkPipelineRasterizationStateCreateInfo pipeline_rasterisation_state_create_info;
					pipeline_rasterisation_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
					pipeline_rasterisation_state_create_info.pNext = NULL;
					pipeline_rasterisation_state_create_info.flags = 0;
					pipeline_rasterisation_state_create_info.depthClampEnable = VK_FALSE;
					pipeline_rasterisation_state_create_info.rasterizerDiscardEnable = VK_FALSE;
					pipeline_rasterisation_state_create_info.polygonMode = VK_POLYGON_MODE_FILL;
					pipeline_rasterisation_state_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
					pipeline_rasterisation_state_create_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
					pipeline_rasterisation_state_create_info.depthBiasEnable = VK_FALSE;
					pipeline_rasterisation_state_create_info.depthBiasConstantFactor = 0.0f;
					pipeline_rasterisation_state_create_info.depthBiasClamp = 0.0f;
					pipeline_rasterisation_state_create_info.depthBiasSlopeFactor = 0.0f;
					pipeline_rasterisation_state_create_info.lineWidth = 1.0f;

					VkPipelineMultisampleStateCreateInfo pipeline_multisample_state_create_info;
					pipeline_multisample_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
					pipeline_multisample_state_create_info.pNext = NULL;
					pipeline_multisample_state_create_info.flags = 0;
					pipeline_multisample_state_create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
					pipeline_multisample_state_create_info.sampleShadingEnable = VK_FALSE;
					pipeline_multisample_state_create_info.minSampleShading = 1.0f;
					pipeline_multisample_state_create_info.pSampleMask = NULL;
					pipeline_multisample_state_create_info.alphaToCoverageEnable = VK_FALSE;
					pipeline_multisample_state_create_info.alphaToOneEnable = VK_FALSE;

					VkPipelineColorBlendAttachmentState pipeline_color_blend_attachment_state;
					pipeline_color_blend_attachment_state.blendEnable = VK_TRUE;
					pipeline_color_blend_attachment_state.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
					pipeline_color_blend_attachment_state.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
					pipeline_color_blend_attachment_state.colorBlendOp = VK_BLEND_OP_ADD;
					pipeline_color_blend_attachment_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
					pipeline_color_blend_attachment_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
					pipeline_color_blend_attachment_state.alphaBlendOp = VK_BLEND_OP_ADD;
					pipeline_color_blend_attachment_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

					VkPipelineColorBlendStateCreateInfo pipeline_color_blend_state_create_info;
					pipeline_color_blend_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
					pipeline_color_blend_state_create_info.pNext = NULL;
					pipeline_color_blend_state_create_info.flags = 0;
					pipeline_color_blend_state_create_info.logicOpEnable = VK_FALSE;
					pipeline_color_blend_state_create_info.logicOp = VK_LOGIC_OP_NO_OP;
					pipeline_color_blend_state_create_info.attachmentCount = 1;
					pipeline_color_blend_state_create_info.pAttachments = &pipeline_color_blend_attachment_state;
					pipeline_color_blend_state_create_info.blendConstants[0] = 0.0f;
					pipeline_color_blend_state_create_info.blendConstants[1] = 0.0f;
					pipeline_color_blend_state_create_info.blendConstants[2] = 0.0f;
					pipeline_color_blend_state_create_info.blendConstants[3] = 0.0f;

					VkPipelineLayoutCreateInfo pipeline_layout_create_info;
					pipeline_layout_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
					pipeline_layout_create_info.pNext = NULL;
					pipeline_layout_create_info.flags = 0;
					pipeline_layout_create_info.setLayoutCount = 0;
					pipeline_layout_create_info.pSetLayouts = NULL;
					pipeline_layout_create_info.pushConstantRangeCount = 0;
					pipeline_layout_create_info.pPushConstantRanges = NULL;

					VkResult result = vkCreatePipelineLayout(api_data->device, &pipeline_layout_create_info, NULL, &api_data->pipeline_layout);
					MTRX_VULKAN_ASSERT("vkCreatePipelineLayout", result, renderer);

					VkAttachmentDescription attachment_description;
					attachment_description.flags = 0;
					attachment_description.format = api_data->format_used;
					attachment_description.samples = VK_SAMPLE_COUNT_1_BIT;
					attachment_description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					attachment_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
					attachment_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					attachment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					attachment_description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					attachment_description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

					VkAttachmentReference attachment_refference;
					attachment_refference.attachment = 0;
					attachment_refference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

					VkSubpassDescription subpass_description;
					subpass_description.flags = 0;
					subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
					subpass_description.inputAttachmentCount = 0;
					subpass_description.pInputAttachments = NULL;
					subpass_description.colorAttachmentCount = 1;
					subpass_description.pColorAttachments = &attachment_refference;
					subpass_description.pResolveAttachments = NULL;
					subpass_description.pDepthStencilAttachment = NULL;
					subpass_description.preserveAttachmentCount = 0;
					subpass_description.pPreserveAttachments = NULL;

					VkSubpassDependency subpass_dependency;
					subpass_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
					subpass_dependency.dstSubpass = 0;
					subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
					subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
					subpass_dependency.srcAccessMask = 0;
					subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
					subpass_dependency.dependencyFlags = 0;

					VkRenderPassCreateInfo render_pass_create_info;
					render_pass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
					render_pass_create_info.pNext = NULL;
					render_pass_create_info.flags = 0;
					render_pass_create_info.attachmentCount = 1;
					render_pass_create_info.pAttachments = &attachment_description;
					render_pass_create_info.subpassCount = 1;
					render_pass_create_info.pSubpasses = &subpass_description;
					render_pass_create_info.dependencyCount = 1;
					render_pass_create_info.pDependencies = &subpass_dependency;

					result = vkCreateRenderPass(api_data->device, &render_pass_create_info, NULL, &api_data->renderer_pass);
					MTRX_VULKAN_ASSERT("vkCreateRenderPass", result, renderer);

					VkGraphicsPipelineCreateInfo graphics_pipeline_create_info;
					graphics_pipeline_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
					graphics_pipeline_create_info.pNext = NULL;
					graphics_pipeline_create_info.flags = 0;
					graphics_pipeline_create_info.stageCount = matrix_vector_capacity(pipeline_shader_stage_create_info_vec);
					graphics_pipeline_create_info.pStages = &MTRX_VECTOR_DATA_AS(VkPipelineShaderStageCreateInfo, pipeline_shader_stage_create_info_vec);
					graphics_pipeline_create_info.pVertexInputState = &pipeline_vertex_input_state_create_info;
					graphics_pipeline_create_info.pInputAssemblyState = &pipelien_input_assembly_state_create_info;
					graphics_pipeline_create_info.pTessellationState = NULL;
					graphics_pipeline_create_info.pViewportState = &pipeline_viewport_state_create_info;
					graphics_pipeline_create_info.pRasterizationState = &pipeline_rasterisation_state_create_info;
					graphics_pipeline_create_info.pMultisampleState = &pipeline_multisample_state_create_info;
					graphics_pipeline_create_info.pDepthStencilState = NULL;
					graphics_pipeline_create_info.pColorBlendState = &pipeline_color_blend_state_create_info;
					graphics_pipeline_create_info.pDynamicState = NULL;
					graphics_pipeline_create_info.layout = api_data->pipeline_layout;
					graphics_pipeline_create_info.renderPass = api_data->renderer_pass;
					graphics_pipeline_create_info.subpass = 0;
					graphics_pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
					graphics_pipeline_create_info.basePipelineIndex = -1;

					result = vkCreateGraphicsPipelines(api_data->device, VK_NULL_HANDLE, 1, &graphics_pipeline_create_info, NULL, &api_data->pipeline);
					MTRX_VULKAN_ASSERT("vkCreateGraphicsPipelines", result, renderer);

					matrix_vector_destruct(&pipeline_shader_stage_create_info_vec);
				}
				else
				{
					MTRX_CORE_LOG("renderer: could not create pipeline -> window is closed", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
				}
			}
		}
	}
}

void matrix_vulkan_create_frame_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			MTRX_CORE_LOG("renderer: framebuffer creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			if (NULL == renderer->window)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				if (matrix_window_opened_is(renderer->window))
				{
					api_data->frame_buffer_all = NULL;
					api_data->frame_buffer_all = malloc(sizeof(*api_data->frame_buffer_all) * api_data->swapchain_image_count);
					if (NULL == api_data->frame_buffer_all)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						VkFramebufferCreateInfo frame_buffer_create_info;
						frame_buffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
						frame_buffer_create_info.pNext = NULL;
						frame_buffer_create_info.flags = 0;
						frame_buffer_create_info.renderPass = api_data->renderer_pass;
						frame_buffer_create_info.attachmentCount = 1;
						frame_buffer_create_info.width = matrix_window_width_get(renderer->window);
						frame_buffer_create_info.height = matrix_window_height_get(renderer->window);
						frame_buffer_create_info.layers = 1;

						for (uint32_t i = 0; i < api_data->swapchain_image_count; i++)
						{
							frame_buffer_create_info.pAttachments = &api_data->image_view_all[i];

							VkResult result = vkCreateFramebuffer(api_data->device, &frame_buffer_create_info, NULL, &api_data->frame_buffer_all[i]);
							int decimals = 1;
							for (int w = i + 1; w >= 10; w /= 10)
							{
								decimals++;
							}
							char* message = NULL;
							message = malloc(sizeof(*message) * (23 + decimals));
							stbsp_sprintf(message, "vkCreateFramebuffer (%u)", i + 1);
							MTRX_VULKAN_ASSERT(message, result, renderer);
							free(message);
						}
					}
				}
				else
				{
					MTRX_CORE_LOG("renderer: could not create framebuffer -> window is closed", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
				}
			}
		}
	}
}

void matrix_vulkan_create_command_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			MTRX_CORE_LOG("renderer: commandbuffer creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			VkCommandPoolCreateInfo command_pool_create_info;
			command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			command_pool_create_info.pNext = NULL;
			command_pool_create_info.flags = 0;
			command_pool_create_info.queueFamilyIndex = 0; //@TODO

			VkResult result = vkCreateCommandPool(api_data->device, &command_pool_create_info, NULL, &api_data->command_pool);
			MTRX_VULKAN_ASSERT("vkCreateCommandPool", result, renderer);

			VkCommandBufferAllocateInfo command_buffer_allocate_info;
			command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			command_buffer_allocate_info.pNext = NULL;
			command_buffer_allocate_info.commandPool = api_data->command_pool;
			command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			command_buffer_allocate_info.commandBufferCount = api_data->swapchain_image_count;

			api_data->command_buffer_all = NULL;
			api_data->command_buffer_all = malloc(sizeof(*api_data->command_buffer_all) * api_data->swapchain_image_count);
			if (NULL == api_data->command_buffer_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				result = vkAllocateCommandBuffers(api_data->device, &command_buffer_allocate_info, api_data->command_buffer_all);
				MTRX_VULKAN_ASSERT("vkAllocateCommandBuffers", result, renderer);

				VkCommandBufferBeginInfo command_buffer_begin_info;
				command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				command_buffer_begin_info.pNext = NULL;
				command_buffer_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
				command_buffer_begin_info.pInheritanceInfo = NULL;

				for (uint32_t i = 0; i < api_data->swapchain_image_count; i++)
				{
					result = vkBeginCommandBuffer(api_data->command_buffer_all[i], &command_buffer_begin_info);
					int decimals = 1;
					for (int w = i + 1; w >= 10; w /= 10)
					{
						decimals++;
					}
					char* message = NULL;
					message = malloc(sizeof(*message) * (24 + decimals));
					stbsp_sprintf(message, "vkBeginCommandBuffer (%u)", i + 1);
					MTRX_VULKAN_ASSERT(message, result, renderer);
					free(message);

					if (NULL == renderer->window)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						if (matrix_window_opened_is(renderer->window))
						{
							VkClearValue clear_value = {0.0f, 0.0f, 0.0f, 1.0f};

							VkRenderPassBeginInfo render_pass_begin_info;
							render_pass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
							render_pass_begin_info.pNext = NULL;
							render_pass_begin_info.renderPass = api_data->renderer_pass;
							render_pass_begin_info.framebuffer = api_data->frame_buffer_all[i];
							render_pass_begin_info.renderArea.offset.x = 0;
							render_pass_begin_info.renderArea.offset.y = 0;
							render_pass_begin_info.renderArea.extent.width = matrix_window_width_get(renderer->window);
							render_pass_begin_info.renderArea.extent.height = matrix_window_height_get(renderer->window);
							render_pass_begin_info.clearValueCount = 1;
							render_pass_begin_info.pClearValues = &clear_value;

							vkCmdBeginRenderPass(api_data->command_buffer_all[i], &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

							vkCmdBindPipeline(api_data->command_buffer_all[i], VK_PIPELINE_BIND_POINT_GRAPHICS, api_data->pipeline);

							vkCmdDraw(api_data->command_buffer_all[i], 3, 1, 0, 0);

							vkCmdEndRenderPass(api_data->command_buffer_all[i]);
						}
						else
						{
							MTRX_CORE_LOG("renderer: could not create framebuffer -> window is closed", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
						}
					}

					result = vkEndCommandBuffer(api_data->command_buffer_all[i]);
					decimals = 1;
					for (int w = i + 1; w >= 10; w /= 10)
					{
						decimals++;
					}
					message = NULL;
					message = malloc(sizeof(*message) * (22 + decimals));
					stbsp_sprintf(message, "vkEndCommandBuffer (%u)", i + 1);
					MTRX_VULKAN_ASSERT(message, result, renderer);
					free(message);
				}
			}
		}
	}
}

void matrix_vulkan_create_semaphore(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			MTRX_CORE_LOG("renderer: semaphore creation", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);

			VkSemaphoreCreateInfo semaphore_create_info;
			semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			semaphore_create_info.pNext = NULL;
			semaphore_create_info.flags = 0;

			VkResult result = vkCreateSemaphore(api_data->device, &semaphore_create_info, NULL, &api_data->semaphore_image_available);
			MTRX_VULKAN_ASSERT("vkCreateSemaphore (1/2)", result, renderer);

			result = vkCreateSemaphore(api_data->device, &semaphore_create_info, NULL, &api_data->semaphore_rendering_done);
			MTRX_VULKAN_ASSERT("vkCreateSemaphore (2/2)", result, renderer);
		}
	}
}

void matrix_vulkan_frame_draw(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			uint32_t image_index = 0;

			VkResult result = vkAcquireNextImageKHR(api_data->device, api_data->swapchain, INT64_MAX, api_data->semaphore_image_available, VK_NULL_HANDLE, &image_index);
			MTRX_VULKAN_QASSERT("vkAcquireNextImageKHR", result, renderer);

			VkPipelineStageFlags wait_stage_mask[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

			VkSubmitInfo submit_info;
			submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submit_info.pNext = NULL;
			submit_info.waitSemaphoreCount = 1;
			submit_info.pWaitSemaphores = &api_data->semaphore_image_available;
			submit_info.pWaitDstStageMask = wait_stage_mask;
			submit_info.commandBufferCount = api_data->swapchain_image_count;
			submit_info.pCommandBuffers = &api_data->command_buffer_all[image_index];
			submit_info.signalSemaphoreCount = 1;
			submit_info.pSignalSemaphores = &api_data->semaphore_rendering_done;

			result = vkQueueSubmit(api_data->queue, 1, &submit_info, VK_NULL_HANDLE);
			MTRX_VULKAN_QASSERT("vkQueueSubmit", result, renderer);

			VkPresentInfoKHR present_info;
			present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			present_info.pNext = NULL;
			present_info.waitSemaphoreCount = 1;
			present_info.pWaitSemaphores = &api_data->semaphore_rendering_done;
			present_info.swapchainCount = 1;
			present_info.pSwapchains = &api_data->swapchain;
			present_info.pImageIndices = &image_index;
			present_info.pResults = NULL;

			result = vkQueuePresentKHR(api_data->queue, &present_info);
			MTRX_VULKAN_QASSERT("vkQueuePresentKHR", result, renderer);
		}
	}
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
			if (NULL == api_data->image_view_all)
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
}

void matrix_vulkan_destroy_shaders(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			if (NULL == api_data->shader_module_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				for (size_t i = 0; i < matrix_vector_capacity(renderer->shader_vec); i++)
				{
					vkDestroyShaderModule(api_data->device, api_data->shader_module_all[i], NULL);
				}

				free(api_data->shader_module_all);

				MTRX_CORE_LOG("renderer: shader destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
			}
		}
	}
}

void matrix_vulkan_destroy_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			vkDestroyPipeline(api_data->device, api_data->pipeline, NULL);
			vkDestroyRenderPass(api_data->device, api_data->renderer_pass, NULL);
			vkDestroyPipelineLayout(api_data->device, api_data->pipeline_layout, NULL);

			MTRX_CORE_LOG("renderer: pipeline destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
}

void matrix_vulkan_destroy_frame_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			if (NULL == api_data->frame_buffer_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				for (uint32_t i = 0; i < api_data->swapchain_image_count; i++)
				{
					vkDestroyFramebuffer(api_data->device, api_data->frame_buffer_all[i], NULL);
				}

				free(api_data->frame_buffer_all);

				MTRX_CORE_LOG("renderer: framebuffer destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
			}
		}
	}
}

void matrix_vulkan_destroy_command_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			vkFreeCommandBuffers(api_data->device, api_data->command_pool, api_data->swapchain_image_count, api_data->command_buffer_all);
			vkDestroyCommandPool(api_data->device, api_data->command_pool, NULL);

			MTRX_CORE_LOG("renderer: commandbuffer destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
}

void matrix_vulkan_destroy_semaphore(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
			vkDestroySemaphore(api_data->device, api_data->semaphore_rendering_done, NULL);
			vkDestroySemaphore(api_data->device, api_data->semaphore_image_available, NULL);

			MTRX_CORE_LOG("renderer: semaphore destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
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