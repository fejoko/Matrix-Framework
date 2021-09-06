#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer.h"

#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Renderer/renderer.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_errors.h"

#ifdef ___MTRX_VULKAN
#include "Matrix/Renderer/INTERNAL/Vulkan/INTERNAL_vulkan.h"
#define MTRX_RENDERER_VULKAN_CONSTRUCT(renderer) matrix_vulkan_construct(renderer)
#define MTRX_RENDERER_VULKAN_INIT(renderer) matrix_vulkan_init(renderer)
#define MTRX_RENDERER_VULKAN_UPDATE(renderer) matrix_vulkan_update(renderer)
#define MTRX_RENDERER_VULKAN_SHUTDOWN(renderer) matrix_vulkan_shutdown(renderer)
#define MTRX_RENDERER_VULKAN_DESTRUCT(renderer) matrix_vulkan_destruct(renderer)
#else
#define MTRX_RENDERER_VULKAN_CONSTRUCT(renderer)
#define MTRX_RENDERER_VULKAN_INIT(renderer)
#define MTRX_RENDERER_VULKAN_UPDATE(renderer)
#define MTRX_RENDERER_VULKAN_SHUTDOWN(renderer)
#define MTRX_RENDERER_VULKAN_DESTRUCT(renderer)
#endif // ___MTRX_VULKAN

#ifdef ___MTRX_OPENGL
#define MTRX_RENDERER_OPENGL_CONSTRUCT(renderer)
#define MTRX_RENDERER_OPENGL_INIT(renderer)
#define MTRX_RENDERER_OPENGL_UPDATE(renderer)
#define MTRX_RENDERER_OPENGL_SHUTDOWN(renderer)
#define MTRX_RENDERER_OPENGL_DESTRUCT(renderer)
#else
#define MTRX_RENDERER_OPENGL_CONSTRUCT(renderer)
#define MTRX_RENDERER_OPENGL_INIT(renderer)
#define MTRX_RENDERER_OPENGL_UPDATE(renderer)
#define MTRX_RENDERER_OPENGL_SHUTDOWN(renderer)
#define MTRX_RENDERER_OPENGL_DESTRUCT(renderer)
#endif // ___MTRX_VULKAN

Matrix_Renderer matrix_renderer_construct()
{
	Matrix_Renderer renderer; renderer.is_active = false;
	renderer.renderer_settings = matrix_renderer_settings_construct();
	renderer.engine = NULL;
	renderer.logger = NULL;
	renderer.window = NULL;
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