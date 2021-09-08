#include "Matrix/Window/window.h"

#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
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
#define MTRX_WINDOW_GLFW_OPEN(width, height, title, window) matrix_glfw_open(width, height, title, window)
#define MTRX_WINDOW_GLFW_CLOSE(window) matrix_glfw_close(window)
#define MTRX_WINDOW_GLFW_SHOULD_CLOSE(window) matrix_glfw_should_close(window)
#else
#define MTRX_WINDOW_GLFW_OPEN(width, height, title, window) MTRX_CORE_LOG("window: could not open window -> glfw not available", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger)
#define MTRX_WINDOW_GLFW_CLOSE(window)
#define MTRX_WINDOW_GLFW_SHOULD_CLOSE(window) false
#endif // ___MTRX_GLFW

#ifdef ___MTRX_WINDOWS
#define MTRX_WINDOW_WINDOWS_OPEN(width, height, title, window) MTRX_CORE_LOG("window: could not open window -> windows_api not yet supported", MATRIX_LOGGER_LEVEL_ERROR, window->logger)
#define MTRX_WINDOW_WINDOWS_CLOSE(window)
#define MTRX_WINDOW_WINDOWS_SHOULD_CLOSE(window) false
#else
#define MTRX_WINDOW_WINDOWS_OPEN(width, height, title, window) MTRX_CORE_LOG("window: could not open window -> windows_api not available", MATRIX_LOGGER_LEVEL_ERROR, window->logger)
#define MTRX_WINDOW_WINDOWS_CLOSE(window)
#define MTRX_WINDOW_WINDOWS_SHOULD_CLOSE(window) false
#endif // ___MTRX_WINDOWS

Matrix_Window_Settings matrix_window_settings_construct()
{
	Matrix_Window_Settings window_settings;
	window_settings.window_api = MATRIX_WINDOW_API_NONE;
	window_settings.window_width_min = 0;
	window_settings.window_height_min = 0;

	return window_settings;
}

void matrix_window_settings_destruct(Matrix_Window_Settings* const window_settings)
{
	if (NULL == window_settings)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_window_settings_set(const Matrix_Window_Settings window_settings, Matrix_Window* window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		window->window_settings = window_settings;
	}
}

void matrix_window_open(int width, int height, const char* title, Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (window->is_opened)
		{
			MTRX_CORE_LOG("window: could not open window -> is already opened", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
		}
		else
		{
			if (width > 0 && height > 0)
			{
				window->width = width;
				window->height = height;
				window->title = title;

				window->is_opened = true;

				switch (window->window_settings.window_api)
				{
				case MATRIX_WINDOW_API_NONE:
					MTRX_CORE_LOG("window: could not open window -> no api selected", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
					break;
				case MATRIX_WINDOW_API_GLFW:
					MTRX_WINDOW_GLFW_OPEN(width, height, title, window);
					break;
				case MATRIX_WINDOW_API_WINDOWS:
					MTRX_WINDOW_WINDOWS_OPEN(width, height, title, window);
					break;
				default:
					MTRX_ERROR_WINDOW_API_OUTOFBOUND;
					break;
				}
			}
			else
			{
				MTRX_CORE_LOG("window: could not open window -> width and height have to be > 0", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
			}
		}
	}
}

void matrix_window_close(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (window->is_opened)
		{
			window->is_opened = false;

			switch (window->window_settings.window_api)
			{
			case MATRIX_WINDOW_API_NONE:
				MTRX_CORE_LOG("window: could not close window -> no api selected", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
				break;
			case MATRIX_WINDOW_API_GLFW:
				MTRX_WINDOW_GLFW_CLOSE(window);
				break;
			case MATRIX_WINDOW_API_WINDOWS:
				MTRX_WINDOW_WINDOWS_CLOSE(window);
				break;
			default:
				MTRX_ERROR_WINDOW_API_OUTOFBOUND;
				break;
			}
		}
		else
		{
			MTRX_CORE_LOG("window: could not close window -> is already closed", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
		}
	}
}

bool matrix_window_opened_is(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return window->is_opened;
	}
}

bool matrix_window_should_close(Matrix_Window* const window)
{
	if (window->is_opened)
	{
		switch (window->window_settings.window_api)
		{
		case MATRIX_WINDOW_API_NONE:
			MTRX_CORE_LOG("window: matrix_window_should_close failed -> no api selected", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
			break;
		case MATRIX_WINDOW_API_GLFW:
			return MTRX_WINDOW_GLFW_SHOULD_CLOSE(window);
		case MATRIX_WINDOW_API_WINDOWS:
			return MTRX_WINDOW_WINDOWS_SHOULD_CLOSE(window);
		default:
			MTRX_ERROR_WINDOW_API_OUTOFBOUND;
			break;
		}

		return false;
	}
	else
	{
		MTRX_CORE_LOG("window: matrix_window_should_close failed -> window is closed", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
	}
}

int matrix_window_width_get(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return window->width;
	}
}

int matrix_window_height_get(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return window->height;
	}
}