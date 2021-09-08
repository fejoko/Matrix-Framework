#include "Matrix/Renderer/renderer.h"

#include "Matrix/Application/application.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Memory/memory.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_errors.h"
 #include "Matrix/Vector/vector.h"	

#include "Stb/stb_sprintf.h"

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

void matrix_renderer_settings_set(const Matrix_Renderer_Settings renderer_settings, Matrix_Renderer* const renderer)
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
				MTRX_CORE_LOG("renderer: could not start renderer -> no api selected", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
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
				MTRX_CORE_LOG("renderer: could not stop renderer -> no api selected", MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
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

void matrix_renderer_shader_load(const char* shader_path_rel, Matrix_Renderer_Shader_Type shader_type, Matrix_Renderer* const renderer)
{
	if (NULL == shader_path_rel)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp("", shader_path_rel))
		{
			if (NULL == matrix_application_path_abs_get(renderer->application))
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				if (strcmp("", matrix_application_path_abs_get(renderer->application)))
				{
					size_t len = strlen(shader_path_rel);
					len += strlen(matrix_application_path_abs_get(renderer->application));

					char* path = NULL;
					path = malloc(sizeof(*path) * len + 1);
					if (NULL == path)
					{
						MTRX_ERROR_MALLOC_FAILED;
					}
					else
					{
						stbsp_sprintf(path, "%s%s", matrix_application_path_abs_get(renderer->application), shader_path_rel);

						uint32_t file_size = 0;
						char* file_data = matrix_memory_file_mapp(path, &file_size);

						char* message = NULL;
						if (NULL == file_data)
						{
							message = malloc(36 + strlen(path) + 1);
							if (NULL == message)
							{
								MTRX_ERROR_MALLOC_FAILED;
							}
							else
							{
								stbsp_sprintf(message, "renderer: failed loading shader at %s", path);
								MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_ERROR, renderer->logger);
								free(message);
							}
						}
						else
						{
							message = malloc(41 + strlen(path) + 1);
							if (NULL == message)
							{
								MTRX_ERROR_MALLOC_FAILED;
							}
							else
							{
								stbsp_sprintf(message, "renderer: succeeded loading shader at \"%s\"", path);
								MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_TRACE, renderer->logger);
								free(message);
							}

							Matrix_Renderer_Shader new_shader;
							new_shader.shader_type = shader_type;
							new_shader.shader_size = file_size;
							new_shader.shader_data = file_data;

							matrix_vector_push_back((char* const)&new_shader, renderer->shader_vec);
						}

						free(path);
					}
				}
				else
				{
					MTRX_ERROR_UNEXPECTED_VALUE;
				}
			}
		}
		else
		{
			MTRX_ERROR_UNEXPECTED_VALUE;
		}
	}
}