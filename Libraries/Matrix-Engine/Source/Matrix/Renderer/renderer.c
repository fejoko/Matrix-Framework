#include "Matrix/Renderer/renderer.h"

#include "Matrix/Core/error.h"
#include "Matrix/Renderer/renderer_data.h"

Matrix_Renderer_Settings matrix_renderer_settings_construct()
{
	Matrix_Renderer_Settings renderer_settings;
	renderer_settings.is_ = false;

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

void matrix_renderer_settings_set(Matrix_Renderer_Settings renderer_settings, Matrix_Renderer* renderer)
{

}