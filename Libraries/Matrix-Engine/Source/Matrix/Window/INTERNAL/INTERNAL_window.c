#include "Matrix/Window/INTERNAL/INTERNAL_window.h"

#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Window/window.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window_data.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window_errors.h"

#ifdef ___MTRX_VULKAN
#define ___MTRX_GLFW
#endif // ___MTRX_VULKAN

#ifdef ___MTRX_OPENGL
#define ___MTRX_GLFW
#endif // ___MTRX_OPENGL

#ifdef ___MTRX_GLFW
#include "Matrix/Window/INTERNAL/Glfw/INTERNAL_glfw.h"
#define MTRX_WINDOW_GLFW_CONSTRUCT(window) matrix_glfw_construct(window)
#define MTRX_WINDOW_GLFW_INIT(window) matrix_glfw_init(window)
#define MTRX_WINDOW_GLFW_UPDATE(window) matrix_glfw_update(window)
#define MTRX_WINDOW_GLFW_SHUTDOWN(window) matrix_glfw_shutdown(window)
#define MTRX_WINDOW_GLFW_DESTRUCT(window) matrix_glfw_destruct(window)
#define MTRX_WINDOW_GLFW_RAW_GET(window) matrix_glfw_raw_get(window)
#else
#define MTRX_WINDOW_GLFW_CONSTRUCT(window)
#define MTRX_WINDOW_GLFW_INIT(window)
#define MTRX_WINDOW_GLFW_UPDATE(window)
#define MTRX_WINDOW_GLFW_SHUTDOWN(window)
#define MTRX_WINDOW_GLFW_DESTRUCT(window)
#define MTRX_WINDOW_GLFW_RAW_GET(window)
#endif // ___MTRX_GLFW

Matrix_Window matrix_window_construct()
{
	Matrix_Window window;
	window.is_opened = false;
	window.window_settings = matrix_window_settings_construct();
	window.logger = NULL;
	window.width = 0;
	window.height = 0;
	window.api_data = NULL;

	MTRX_WINDOW_GLFW_CONSTRUCT(&window);

	return window;
}

void matrix_window_destruct(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		MTRX_WINDOW_GLFW_DESTRUCT(window);
	}
}

void matrix_window_init(Matrix_Logger* const logger, Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		window->logger = logger;

		MTRX_WINDOW_GLFW_INIT(window);

		MTRX_CORE_LOG("window: initialisation", MATRIX_LOGGER_LEVEL_INFO, logger);
	}
}

void matrix_window_update(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		switch (window->window_settings.window_api)
		{
		case MATRIX_WINDOW_API_NONE:
			break;
		case MATRIX_WINDOW_API_GLFW:
			MTRX_WINDOW_GLFW_UPDATE(window);
			break;
		case MATRIX_WINDOW_API_WINDOWS:
			break;
		default:
			MTRX_ERROR_WINDOW_API_OUTOFBOUND;
			break;
		}
	}
}

void matrix_window_shutdown(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		MTRX_WINDOW_GLFW_SHUTDOWN(window);

		MTRX_CORE_LOG("window: shutdown", MATRIX_LOGGER_LEVEL_INFO, window->logger);
	}
}

Matrix_Window_Api matrix_window_api_get(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return window->window_settings.window_api;
	}
}

void* matrix_window_raw_get(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		switch (window->window_settings.window_api)
		{
		case MATRIX_WINDOW_API_NONE:
			break;
		case MATRIX_WINDOW_API_GLFW:
			return MTRX_WINDOW_GLFW_RAW_GET(window);
		case MATRIX_WINDOW_API_WINDOWS:
			break;
		default:
			MTRX_ERROR_WINDOW_API_OUTOFBOUND;
			break;
		}
	}
}