#include "Matrix/Window/INTERNAL/Glfw/INTERNAL_glfw.h"

#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window_data.h"
#include "Matrix/Window/INTERNAL/Glfw/INTERNAL_glfw_data.h"
#include "Matrix/Window/INTERNAL/Glfw/INTERNAL_glfw_errors.h"

void matrix_glfw_construct(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		window->api_data = NULL;
		window->api_data = malloc(sizeof(Matrix_Glfw_Data));
		if (NULL == window->api_data)
		{
			MTRX_ERROR_MALLOC_FAILED;
		}
		else
		{

		}
	}
}

void matrix_glfw_init(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (GLFW_TRUE == glfwInit())
		{
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}
		else
		{
			MTRX_CORE_LOG("window: could not init glfw", MATRIX_LOGGER_LEVEL_ERROR, window->logger);
		}
	}
}

void matrix_glfw_open(int width, int height, const char* title, Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		((Matrix_Glfw_Data*)window->api_data)->glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
	}
}

void matrix_glfw_update(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		glfwPollEvents();
	}
}

void matrix_glfw_close(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		glfwDestroyWindow(((Matrix_Glfw_Data*)window->api_data)->glfw_window);
	}
}

void matrix_glfw_shutdown(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		glfwTerminate();
	}
}

void matrix_glfw_destruct(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		free(window->api_data);
	}
}

bool matrix_glfw_should_close(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return glfwWindowShouldClose(((Matrix_Glfw_Data*)window->api_data)->glfw_window);
	}
}

void* matrix_glfw_raw_get(Matrix_Window* const window)
{
	if (NULL == window)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return ((Matrix_Glfw_Data*)window->api_data)->glfw_window;
	}
}