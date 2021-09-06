#include "Matrix/Engine/INTERNAL/INTERNAL_engine.h"

#include "Matrix/Application/INTERNAL/INTERNAL_application.h"
#include "Matrix/Console/console.h"
#include "Matrix/Core/core.h"
#include "Matrix/Core/error.h"
#include "Matrix/Engine/engine.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"
#include "Matrix/Time/INTERNAL/INTERNAL_time.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window.h"

Matrix_Engine matrix_engine_construct()
{
	Matrix_Engine engine = { "matrix", __DATE__, __TIME__, MTRX_VERSION_MAKE(0, 0, 1, 0) };
	engine.is_stop = false;
	engine.engine_settings = matrix_engine_settings_construct();
	engine.time_ = matrix_time_construct();
	engine.logger = matrix_logger_construct();
	engine.window = matrix_window_construct();
	engine.renderer = matrix_renderer_construct();
	engine.statemanager = matrix_statemanager_construct();
	engine.application = matrix_applicatione_construct();

	return engine;
}

void matrix_engine_destruct(Matrix_Engine* const engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_application_destruct(&engine->application);
		matrix_renderer_destruct(&engine->renderer);
		matrix_window_destruct(&engine->window);
		matrix_statemanager_destruct(&engine->statemanager);
		matrix_logger_destruct(&engine->logger);
		matrix_time_destruct(&engine->time_);
		matrix_engine_settings_destruct(&engine->engine_settings);
	}
}

void matrix_engine_init(Matrix_Engine* const engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		engine->data.engine = engine;
		engine->data.logger = &engine->logger;
		engine->data.window = &engine->window;
		engine->data.renderer = &engine->renderer;
		engine->data.statemanager = &engine->statemanager;
		engine->data.application = &engine->application;

		matrix_application_attach(&engine->application);

		MTRX_CORE_PRELOG("engine: initialisation", MATRIX_LOGGER_LEVEL_INFO, &engine->application);

		if (NULL != engine->application.application_core.engine_setup)
		{
			engine->application.application_core.engine_setup(engine);
		}

		matrix_time_init(&engine->application, &engine->time_);

		matrix_logger_init(engine, &engine->application, &engine->time_, &engine->logger);

		if (NULL != engine->application.application_core.logger_setup)
		{
			engine->application.application_core.logger_setup(&engine->logger);
		}

		matrix_window_init(&engine->logger, &engine->window);

		if (NULL != engine->application.application_core.window_setup)
		{
			engine->application.application_core.window_setup(&engine->window);
		}

		matrix_renderer_init(engine, &engine->application, &engine->logger, &engine->window, &engine->renderer);

		if (NULL != engine->application.application_core.renderer_setup)
		{
			engine->application.application_core.renderer_setup(&engine->renderer);
		}

		matrix_statemanager_init(&engine->logger, &engine->data, &engine->statemanager);

		if (NULL != engine->application.application_core.statemanager_setup)
		{
			engine->application.application_core.statemanager_setup(&engine->statemanager);
		}

		matrix_statemanager_start(&engine->statemanager);
	}
}

void matrix_engine_update(Matrix_Engine* const engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_update(&engine->time_);
		matrix_window_update(&engine->window);
		matrix_renderer_update(&engine->renderer);
		matrix_statemanager_update(&engine->statemanager);
	}
}

void matrix_engine_shutdown(Matrix_Engine* const engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_statemanager_shutdown(&engine->statemanager);
		matrix_renderer_shutdown(&engine->renderer);
		matrix_window_shutdown(&engine->window);
		matrix_logger_shutdown(&engine->logger);
		matrix_time_shutdown(&engine->time_);

		MTRX_CORE_PRELOG("engine: shutdown", MATRIX_LOGGER_LEVEL_INFO, &engine->application);
	}
}

void matrix_engine_start(Matrix_Engine* const engine)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_engine_init(engine);
		while (!engine->is_stop)
		{
			matrix_engine_update(engine);
		}
		matrix_engine_shutdown(engine);
	}
}