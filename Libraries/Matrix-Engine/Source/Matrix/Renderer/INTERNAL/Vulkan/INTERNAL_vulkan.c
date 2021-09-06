#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan.h"

#include "Matrix/Application/application_data.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_errors.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_helpers.h"

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
			const char** enabled_extentions = { "" };

			VkInstanceCreateInfo instance_create_info;
			instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instance_create_info.pNext = NULL;
			instance_create_info.flags = 0;
			instance_create_info.pApplicationInfo = &application_info;
			instance_create_info.enabledLayerCount = enabled_layers_count;
			instance_create_info.ppEnabledLayerNames = enabled_layers;
			instance_create_info.enabledExtensionCount = enabled_extentions_count;
			instance_create_info.ppEnabledExtensionNames = &enabled_extentions;

			VkResult result = vkCreateInstance(&instance_create_info, NULL, &api_data->instance);
			matrix_vulkan_assert_result("vkCreateInstance", result, renderer);
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

			api_data->physical_device_amount = 0;
			VkResult result = vkEnumeratePhysicalDevices(api_data->instance, &api_data->physical_device_amount, NULL);
			matrix_vulkan_assert_result("vkEnumeratePhysicalDevices (1/2)", result, renderer);
			api_data->physical_device_all = NULL;
			api_data->physical_device_all = malloc(sizeof(*api_data->physical_device_all) * api_data->physical_device_amount);
			if (NULL == api_data->physical_device_all)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				result = vkEnumeratePhysicalDevices(api_data->instance, &api_data->physical_device_amount, api_data->physical_device_all);
				matrix_vulkan_assert_result("vkEnumeratePhysicalDevices (2/2)", result, renderer);

				api_data->physical_device_all_properties = NULL;
				api_data->physical_device_all_properties = malloc(sizeof(*api_data->physical_device_all_properties) * api_data->physical_device_amount);
				if (NULL == api_data->physical_device_all_properties)
				{
					MTRX_ERROR_UNEXPECTED_NULL;
				}
				else
				{
					api_data->physical_device_all_features = NULL;
					api_data->physical_device_all_features = malloc(sizeof(*api_data->physical_device_all_features) * api_data->physical_device_amount);
					if (NULL == api_data->physical_device_all_features)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						api_data->physical_device_all_memory_properties = NULL;
						api_data->physical_device_all_memory_properties = malloc(sizeof(*api_data->physical_device_all_memory_properties) * api_data->physical_device_amount);
						if (NULL == api_data->physical_device_all_memory_properties)
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							for (uint32_t i = 0; i < api_data->physical_device_amount; i++)
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
				
				//VkBool32 is_swapchain_supported = VK_FALSE;
				//VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(api_data->physical_device_all[api_data->physical_device_used_index], 0, api_data->surface, &is_swapchain_supported);
				//matrix_vulkan_assert_result("vkGetPhysicalDeviceSurfaceSupportKHR", result, renderer);
				//if (is_swapchain_supported == VK_FALSE)
				//{
				//	MTRX_CORE_LOG("renderer: surface not supported", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
				//}
				
				uint32_t enabled_layers_count = MTRX_VULKAN_ENABLED_DEVICE_LAYERS_COUNT;
				const char* enabled_layers[] = { MTRX_VULKAN_ENABLED_DEVICE_LAYERS };
				
				uint32_t enabled_extentions_count = 0;
				const char* enabled_extentions[] = { "" };
				
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

void matrix_vulkan_create_swapchain(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_create_imageviews(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_create_shaders(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_create_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
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
						}

						free(api_data->physical_device_all_features);
					}

					free(api_data->physical_device_all_properties);
				}

				free(api_data->physical_device_all);
			}

			MTRX_CORE_LOG("renderer: physical_device denumeration", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
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
			}

			vkDestroyDevice(api_data->device, NULL);

			MTRX_CORE_LOG("renderer: device destruction", MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
		}
	}
}

void matrix_vulkan_destroy_swapchain(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_destroy_imageviews(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_destroy_shaders(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}

void matrix_vulkan_destroy_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer)
{

}