#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer.h"

#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Renderer/renderer.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_errors.h"
#include "Matrix/Vector/vector.h"

#ifdef ___MTRX_VULKAN
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan.h"
#define MTRX_RENDERER_VULKAN_CONSTRUCT(renderer) matrix_vulkan_construct(renderer)
#define MTRX_RENDERER_VULKAN_INIT(renderer) matrix_vulkan_init(renderer)
#define MTRX_RENDERER_VULKAN_UPDATE(renderer) matrix_vulkan_update(renderer)
#define MTRX_RENDERER_VULKAN_SHUTDOWN(renderer) matrix_vulkan_shutdown(renderer)
#define MTRX_RENDERER_VULKAN_DESTRUCT(renderer) matrix_vulkan_destruct(renderer)
#define MTRX_RENDERER_VULKAN_ONRESIZE(renderer) matrix_vulkan_onResize(renderer)
#else
#define MTRX_RENDERER_VULKAN_CONSTRUCT(renderer)
#define MTRX_RENDERER_VULKAN_INIT(renderer)
#define MTRX_RENDERER_VULKAN_UPDATE(renderer)
#define MTRX_RENDERER_VULKAN_SHUTDOWN(renderer)
#define MTRX_RENDERER_VULKAN_DESTRUCT(renderer)
#define MTRX_RENDERER_VULKAN_ONRESIZE(renderer)
#endif // ___MTRX_VULKAN

#ifdef ___MTRX_OPENGL
#define MTRX_RENDERER_OPENGL_CONSTRUCT(renderer)
#define MTRX_RENDERER_OPENGL_INIT(renderer)
#define MTRX_RENDERER_OPENGL_UPDATE(renderer)
#define MTRX_RENDERER_OPENGL_SHUTDOWN(renderer)
#define MTRX_RENDERER_OPENGL_DESTRUCT(renderer)
#define MTRX_RENDERER_OPENGL_ONRESIZE(renderer)
#else
#define MTRX_RENDERER_OPENGL_CONSTRUCT(renderer)
#define MTRX_RENDERER_OPENGL_INIT(renderer)
#define MTRX_RENDERER_OPENGL_UPDATE(renderer)
#define MTRX_RENDERER_OPENGL_SHUTDOWN(renderer)
#define MTRX_RENDERER_OPENGL_DESTRUCT(renderer)
#define MTRX_RENDERER_OPENGL_ONRESIZE(renderer)
#endif // ___MTRX_VULKAN

Matrix_Renderer matrix_renderer_construct()
{
	Matrix_Renderer renderer;
	renderer.is_active = false;
	renderer.renderer_settings = matrix_renderer_settings_construct();
	renderer.engine = NULL;
	renderer.logger = NULL;
	renderer.window = NULL;
	renderer.shader_vec = matrix_vector_construct(sizeof(Matrix_Renderer_Shader), 0);
	renderer.api_data = NULL;

	MTRX_RENDERER_VULKAN_CONSTRUCT(&renderer);
	MTRX_RENDERER_OPENGL_CONSTRUCT(&renderer);

	return renderer;
}

void matrix_renderer_destruct(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		MTRX_RENDERER_OPENGL_DESTRUCT(renderer);
		MTRX_RENDERER_VULKAN_DESTRUCT(renderer);

		matrix_renderer_settings_destruct(&renderer->renderer_settings);

		matrix_vector_destruct(&renderer->shader_vec);
	}
}

void matrix_renderer_init(Matrix_Engine* const engine, Matrix_Application* const application, Matrix_Logger* const logger, Matrix_Window* const window, Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		renderer->engine = engine;
		renderer->application = application;
		renderer->logger = logger;
		renderer->window = window;

		MTRX_CORE_LOG("renderer: initialisation", MATRIX_LOGGER_LEVEL_INFO, logger);

		MTRX_RENDERER_VULKAN_INIT(renderer);
		MTRX_RENDERER_OPENGL_INIT(renderer);
	}
}

void matrix_renderer_update(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		MTRX_RENDERER_VULKAN_UPDATE(renderer);
		MTRX_RENDERER_OPENGL_UPDATE(renderer);
	}
}

void matrix_renderer_shutdown(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		MTRX_RENDERER_OPENGL_SHUTDOWN(renderer);
		MTRX_RENDERER_VULKAN_SHUTDOWN(renderer);

		MTRX_CORE_LOG("renderer: shutdown", MATRIX_LOGGER_LEVEL_INFO, renderer->logger);
	}
}

void matrix_renderer_onResize(Matrix_Renderer* const renderer)
{
	if (NULL == renderer)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (renderer->is_active)
		{
			switch (renderer->renderer_settings.renderer_api)
			{
			case MATRIX_RENDERER_API_NONE:
				MTRX_CORE_LOG("renderer: could not resize renderer -> no api selected", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
				break;
			case MATRIX_RENDERER_API_VULKAN:
				MTRX_RENDERER_VULKAN_ONRESIZE(renderer);
				break;
			case MATRIX_RENDERER_API_OPENGL:
				MTRX_RENDERER_OPENGL_ONRESIZE(renderer);
				break;
			default:
				MTRX_ERROR_RENDERER_API_OUTOFBOUND;
				break;
			}
		}
		else
		{
			//nothing
		}
	}
}