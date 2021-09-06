#include "Matrix/Renderer/renderer.h"

#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_errors.h"

#ifdef ___MTRX_VULKAN
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan.h"
#define MTRX_RENDERER_VULKAN_START(renderer) matrix_vulkan_start(renderer)
#define MTRX_RENDERER_VULKAN_STOP(renderer) matrix_vulkan_stop(renderer)
#else
#define MTRX_RENDERER_VULKAN_START(renderer) MTRX_CORE_LOG("renderer: could not start renderer -> vulkan not available", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger)
#define MTRX_RENDERER_VULKAN_STOP(renderer)
#endif // ___MTRX_VULKAN

#ifdef ___MTRX_OPENGL
#define MTRX_RENDERER_OPENGL_START(renderer) MTRX_CORE_LOG("renderer: could not start renderer -> opengl not yet supported", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger)
#define MTRX_RENDERER_OPENGL_STOP(renderer)
#else
#define MTRX_RENDERER_OPENGL_START(renderer) MTRX_CORE_LOG("renderer: could not start renderer -> opengl not available", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger)
#define MTRX_RENDERER_OPENGL_STOP(renderer)
#endif // ___MTRX_VULKAN

Matrix_Renderer_Settings matrix_renderer_settings_construct()
{
	Matrix_Renderer_Settings renderer_settings;
	renderer_settings.renderer_api = MATRIX_RENDERER_API_NONE;

	return renderer_settings;
}

void matrix_renderer_settings_destruct(Matrix_Renderer_Settings* const renderer_settings)
{
	if (NULL == renderer_settings)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_renderer_settings_set(const Matrix_Renderer_Settings renderer_settings, Matrix_Renderer* renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		renderer->renderer_settings = renderer_settings;
	}
}

void matrix_renderer_start(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (renderer->is_active)
		{
			MTRX_CORE_LOG("renderer: is already started", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
		}
		else
		{
			renderer->is_active = true;

			switch (renderer->renderer_settings.renderer_api)
			{
			case MATRIX_RENDERER_API_NONE:
				break;
			case MATRIX_RENDERER_API_VULKAN:
				MTRX_RENDERER_VULKAN_START(renderer);
				break;
			case MATRIX_RENDERER_API_OPENGL:
				MTRX_RENDERER_OPENGL_START(renderer);
				break;
			default:
				MTRX_ERROR_RENDERER_API_OUTOFBOUND;
				break;
			}
		}
	}
}

void matrix_renderer_stop(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (renderer->is_active)
		{
			renderer->is_active = false;

			switch (renderer->renderer_settings.renderer_api)
			{
			case MATRIX_RENDERER_API_NONE:
				break;
			case MATRIX_RENDERER_API_VULKAN:
				MTRX_RENDERER_VULKAN_STOP(renderer);
				break;
			case MATRIX_RENDERER_API_OPENGL:
				MTRX_RENDERER_OPENGL_STOP(renderer);
				break;
			default:
				MTRX_ERROR_RENDERER_API_OUTOFBOUND;
				break;
			}
		}
		else
		{
			MTRX_CORE_LOG("renderer: is already stopped", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
		}
	}
}