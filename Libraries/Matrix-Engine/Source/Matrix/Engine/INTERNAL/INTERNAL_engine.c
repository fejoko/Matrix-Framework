#include "Matrix/Engine/INTERNAL/INTERNAL_engine.h"

#include "Matrix/Application/INTERNAL/INTERNAL_application.h"
#include "Matrix/Core/core.h"
#include "Matrix/Core/error.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"

Matrix_Engine_Info matrix_INTERNAL_engine_info_construct()
{
	Matrix_Engine_Info engine_info = {"matrix", __DATE__, __TIME__, MTRX_VERSION_MAKE(0, 0, 1, 0)};

	return engine_info;
}

void matrix_INTERNAL_engine_init(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_application_attach(&engine->application);

		if (NULL != engine->application.application_core.engine_setup)
		{
			engine->application.application_core.engine_setup(engine);
		}

		if (NULL != engine->application.application_core.statemanager_setup)
		{
			engine->application.application_core.statemanager_setup(&engine->statemanager);
		}

		matrix_statemanager_init(&engine->statemanager);
	}
}

void matrix_INTERNAL_engine_update(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_statemanager_update(&engine->statemanager);
	}
}

void matrix_INTERNAL_engine_shutdown(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_statemanager_shutdown(&engine->statemanager);
	}
}

Matrix_Engine matrix_engine_construct()
{
	Matrix_Engine engine = { matrix_INTERNAL_engine_info_construct() };
	engine.is_stop = false;
	engine.engine_settings.i = 0;
	engine.application = matrix_applicatione_construct();
	engine.statemanager = matrix_statemanager_construct();

	return engine;
}

void matrix_engine_destruct(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_statemanager_destruct(&engine->statemanager);
	}
}

void matrix_engine_run(Matrix_Engine* engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_INTERNAL_engine_init(engine);
		while (!engine->is_stop)
		{
			matrix_INTERNAL_engine_update(engine);
		}
		matrix_INTERNAL_engine_shutdown(engine);
	}
}