#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_helpers.h"

#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan_errors.h"

#include "Stb/stb_sprintf.h"

void matrix_vulkan_assert_result(const char* what, VkResult result, Matrix_Renderer* const renderer)
{
	if (VK_SUCCESS == result)
	{
		char* message = NULL;
		message = malloc(sizeof(*message) * (37 + strlen(what)));
		if (NULL == message)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
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
		const char* result_name = "";

		switch (result)
		{
		case VK_NOT_READY:
			result_name = "VK_NOT_READY";
			break;
		case VK_TIMEOUT:
			result_name = "VK_TIMEOUT";
			break;
		case VK_EVENT_SET:
			result_name = "VK_EVENT_SET";
			break;
		case VK_EVENT_RESET:
			result_name = "VK_EVENT_RESET";
			break;
		case VK_INCOMPLETE:
			result_name = "VK_INCOMPLETE";
			break;
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			result_name = "VK_ERROR_OUT_OF_HOST_MEMORY";
			break;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			result_name = "VK_ERROR_OUT_OF_DEVICE_MEMORY";
			break;
		case VK_ERROR_INITIALIZATION_FAILED:
			result_name = "VK_ERROR_INITIALIZATION_FAILED";
			break;
		case VK_ERROR_DEVICE_LOST:
			result_name = "VK_ERROR_DEVICE_LOST";
			break;
		case VK_ERROR_MEMORY_MAP_FAILED:
			result_name = "VK_ERROR_MEMORY_MAP_FAILED";
			break;
		case VK_ERROR_LAYER_NOT_PRESENT:
			result_name = "VK_ERROR_LAYER_NOT_PRESENT";
			break;
		case VK_ERROR_EXTENSION_NOT_PRESENT:
			result_name = "VK_ERROR_EXTENSION_NOT_PRESENT";
			break;
		case VK_ERROR_FEATURE_NOT_PRESENT:
			result_name = "VK_ERROR_FEATURE_NOT_PRESENT";
			break;
		case VK_ERROR_INCOMPATIBLE_DRIVER:
			result_name = "VK_ERROR_INCOMPATIBLE_DRIVER";
			break;
		case VK_ERROR_TOO_MANY_OBJECTS:
			result_name = "VK_ERROR_TOO_MANY_OBJECTS";
			break;
		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			result_name = "VK_ERROR_FORMAT_NOT_SUPPORTED";
			break;
		case VK_ERROR_FRAGMENTED_POOL:
			result_name = "VK_ERROR_FRAGMENTED_POOL";
			break;
		case VK_ERROR_UNKNOWN:
			result_name = "VK_ERROR_UNKNOWN (check vulkan man)";
			break;
		case VK_ERROR_OUT_OF_POOL_MEMORY:
			result_name = "VK_ERROR_OUT_OF_POOL_MEMORY/VK_ERROR_OUT_OF_POOL_MEMORY_KHR";
			break;
		case VK_ERROR_INVALID_EXTERNAL_HANDLE:
			result_name = "VK_ERROR_INVALID_EXTERNAL_HANDLE/VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR";
			break;
		case VK_ERROR_FRAGMENTATION:
			result_name = "VK_ERROR_FRAGMENTATION/VK_ERROR_FRAGMENTATION_EXT";
			break;
		case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
			result_name = "VK_ERROR_INVALID_ - OPAQUE_CAPTURE_ADDRESS/DEVICE_ADDRESS_EXT/OPAQUE_CAPTURE_ADDRESS_KHR/OPAQUE_CAPTURE_ADDRESS_KHR";
			break;
		case VK_ERROR_SURFACE_LOST_KHR:
			result_name = "VK_ERROR_SURFACE_LOST_KHR";
			break;
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			result_name = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			break;
		case VK_SUBOPTIMAL_KHR:
			result_name = "VK_SUBOPTIMAL_KHR";
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
			result_name = "VK_ERROR_OUT_OF_DATE_KHR";
			break;
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			result_name = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			break;
		case VK_ERROR_VALIDATION_FAILED_EXT:
			result_name = "VK_ERROR_VALIDATION_FAILED_EXT";
			break;
		case VK_ERROR_INVALID_SHADER_NV:
			result_name = "VK_ERROR_INVALID_SHADER_NV";
			break;
		case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
			result_name = "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
			break;
		case VK_ERROR_NOT_PERMITTED_EXT:
			result_name = "VK_ERROR_NOT_PERMITTED_EXT";
			break;
		case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
			result_name = "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
			break;
		case VK_THREAD_IDLE_KHR:
			result_name = "VK_THREAD_IDLE_KHR";
			break;
		case VK_THREAD_DONE_KHR:
			result_name = "VK_THREAD_DONE_KHR";
			break;
		case VK_OPERATION_DEFERRED_KHR:
			result_name = "VK_OPERATION_DEFERRED_KHR";
			break;
		case VK_OPERATION_NOT_DEFERRED_KHR:
			result_name = "VK_OPERATION_NOT_DEFERRED_KHR";
			break;
		case VK_PIPELINE_COMPILE_REQUIRED_EXT:
			result_name = "VK_PIPELINE_COMPILE_REQUIRED_EXT/VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT";
			break;
		case VK_RESULT_MAX_ENUM:
			result_name = "VK_RESULT_MAX_ENUM";
			break;
		default:
			MTRX_ERROR_VULKAN_VKRESULT_OUTOFBOUND;
			break;
		}

		char* message = NULL;
		message = malloc(sizeof(*message)* (28 + strlen(what) + strlen(result_name) + 1));
		if (NULL == message)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			stbsp_sprintf(message, "renderer: %s failed with %s", what, result_name);
			MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
			free(message);
		}
	}
}