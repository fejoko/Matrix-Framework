#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_helpers.h"

#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_errors.h"

#include "Stb/stb_sprintf.h"

const char* matrix_renderer_result_match(VkResult result)
{
	switch (result)
	{
	case VK_NOT_READY:
		return "VK_NOT_READY";
	case VK_TIMEOUT:
		return "VK_TIMEOUT";
	case VK_EVENT_SET:
		return "VK_EVENT_SET";
	case VK_EVENT_RESET:
		return "VK_EVENT_RESET";
	case VK_INCOMPLETE:
		return "VK_INCOMPLETE";
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		return "VK_ERROR_OUT_OF_HOST_MEMORY";
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
	case VK_ERROR_INITIALIZATION_FAILED:
		return "VK_ERROR_INITIALIZATION_FAILED";
	case VK_ERROR_DEVICE_LOST:
		return "VK_ERROR_DEVICE_LOST";
	case VK_ERROR_MEMORY_MAP_FAILED:
		return "VK_ERROR_MEMORY_MAP_FAILED";
	case VK_ERROR_LAYER_NOT_PRESENT:
		return "VK_ERROR_LAYER_NOT_PRESENT";
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		return "VK_ERROR_EXTENSION_NOT_PRESENT";
	case VK_ERROR_FEATURE_NOT_PRESENT:
		return "VK_ERROR_FEATURE_NOT_PRESENT";
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		return "VK_ERROR_INCOMPATIBLE_DRIVER";
	case VK_ERROR_TOO_MANY_OBJECTS:
		return "VK_ERROR_TOO_MANY_OBJECTS";
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		return "VK_ERROR_FORMAT_NOT_SUPPORTED";
	case VK_ERROR_FRAGMENTED_POOL:
		return "VK_ERROR_FRAGMENTED_POOL";
	case VK_ERROR_UNKNOWN:
		return "VK_ERROR_UNKNOWN (check vulkan man)";
	case VK_ERROR_OUT_OF_POOL_MEMORY:
		return "VK_ERROR_OUT_OF_POOL_MEMORY/VK_ERROR_OUT_OF_POOL_MEMORY_KHR";
	case VK_ERROR_INVALID_EXTERNAL_HANDLE:
		return "VK_ERROR_INVALID_EXTERNAL_HANDLE/VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR";
	case VK_ERROR_FRAGMENTATION:
		return "VK_ERROR_FRAGMENTATION/VK_ERROR_FRAGMENTATION_EXT";
	case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
		return "VK_ERROR_INVALID_ - OPAQUE_CAPTURE_ADDRESS/DEVICE_ADDRESS_EXT/OPAQUE_CAPTURE_ADDRESS_KHR/OPAQUE_CAPTURE_ADDRESS_KHR";
	case VK_ERROR_SURFACE_LOST_KHR:
		return "VK_ERROR_SURFACE_LOST_KHR";
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		return  "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
	case VK_SUBOPTIMAL_KHR:
		return  "VK_SUBOPTIMAL_KHR";
	case VK_ERROR_OUT_OF_DATE_KHR:
		return "VK_ERROR_OUT_OF_DATE_KHR";
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
	case VK_ERROR_VALIDATION_FAILED_EXT:
		return "VK_ERROR_VALIDATION_FAILED_EXT";
	case VK_ERROR_INVALID_SHADER_NV:
		return "VK_ERROR_INVALID_SHADER_NV";
	case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
		return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
	case VK_ERROR_NOT_PERMITTED_EXT:
		return "VK_ERROR_NOT_PERMITTED_EXT";
	case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
		return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
	case VK_THREAD_IDLE_KHR:
		return "VK_THREAD_IDLE_KHR";
	case VK_THREAD_DONE_KHR:
		return "VK_THREAD_DONE_KHR";
	case VK_OPERATION_DEFERRED_KHR:
		return "VK_OPERATION_DEFERRED_KHR";
	case VK_OPERATION_NOT_DEFERRED_KHR:
		return "VK_OPERATION_NOT_DEFERRED_KHR";
	case VK_PIPELINE_COMPILE_REQUIRED_EXT:
		return "VK_PIPELINE_COMPILE_REQUIRED_EXT/VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT";
	case VK_RESULT_MAX_ENUM:
		return "VK_RESULT_MAX_ENUM";
	default:
		MTRX_ERROR_VULKAN_VKRESULT_OUTOFBOUND;
		break;
	}
}

void matrix_renderer_vulkan_assert(const char* what, VkResult result, Matrix_Renderer* const renderer)
{
	char* message = NULL;

	if (VK_SUCCESS == result)
	{
		message = malloc(sizeof(*message) * (37 + strlen(what)));
		if (NULL == message)
		{
			MTRX_ERROR_MALLOC_FAILED;
		}
		else
		{
			stbsp_sprintf(message, "renderer: %s succeeded with VK_SUCCESS", what);
			MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_DEBUG, renderer->logger);
			free(message);
		}
	}
	else
	{
		const char* result_name = matrix_renderer_result_match(result);

		message = malloc(sizeof(*message)* (24 + strlen(what) + strlen(result_name)));
		if (NULL == message)
		{
			MTRX_ERROR_MALLOC_FAILED;
		}
		else
		{
			stbsp_sprintf(message, "renderer: %s failed with %s", what, result_name);
			MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
			free(message);
		}
	}
}

void matrix_renderer_vulkan_assert_index(const char* what, VkResult result, uint64_t index, Matrix_Renderer* const renderer)
{
	int decimals = 1;
	for (int w = index + 1; w >= 10; w /= 10)
	{
		decimals++;
	}
	char* message = NULL;
	if (NULL == what)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (0 == what)
		{
			MTRX_ERROR_UNEXPECTED_VALUE;
		}
		else
		{
			if (VK_SUCCESS == result)
			{
				message = malloc(sizeof(*message) * (40 + decimals + strlen(what)));
				if (NULL == message)
				{
					MTRX_ERROR_MALLOC_FAILED;
				}
				else
				{
					stbsp_sprintf(message, "renderer: %s (%u) succeeded with VK_SUCCESS", what, decimals);
					MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_DEBUG, renderer->logger);
					free(message);
				}
			}
			else
			{
				const char* result_name = matrix_renderer_result_match(result);

				message = malloc(sizeof(*message) * (27 + decimals + strlen(what) + strlen(result_name)));
				if (NULL == message)
				{
					MTRX_ERROR_MALLOC_FAILED;
				}
				else
				{
					stbsp_sprintf(message, "renderer: %s (%u) failed with %s", what, index + 1);
					MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
					free(message);
				}
			}
		}
	}
}

void matrix_renderer_vulkan_assert_quiet(const char* what, VkResult result, Matrix_Renderer* const renderer)
{
	char* message = NULL;

	if (VK_SUCCESS == result)
	{
		//nothing
	}
	else
	{
		const char* result_name = matrix_renderer_result_match(result);

		if (NULL == what)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			if (0 == what)
			{
				MTRX_ERROR_UNEXPECTED_VALUE;
			}
			else
			{
				message = malloc(sizeof(*message) * (24 + strlen(what) + strlen(result_name)));
				if (NULL == message)
				{
					MTRX_ERROR_MALLOC_FAILED;
				}
				else
				{
					stbsp_sprintf(message, "renderer: %s failed with %s", what, result_name);
					MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
					free(message);
				}
			}
		}
	}
}