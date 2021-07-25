#include "Matrix/Engine/engine.h"

#include "Matrix/Core/error.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"

Matrix_Engine_Info matrix_engine_info_get(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return engine->engine_info;
	}
}

Matrix_Engine_Settings matrix_engine_settings_construct()
{
	Matrix_Engine_Settings engine_settings;
	engine_settings.i = 0;

	return engine_settings;
}

void matrix_engine_settings_destruct(Matrix_Engine_Settings* engine_settings)
{

}

void matrix_engine_settings_set(Matrix_Engine_Settings engine_settings, Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		engine->engine_settings = engine_settings;
	}
}

void matrix_engine_stop(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		engine->is_stop = true;
	}
}

bool matrix_engine_stop_is(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return engine->is_stop;
	}
}