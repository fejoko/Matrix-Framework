#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"

#include "Matrix/Core/error.h"
#include "Matrix/Engine/engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_errors.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_helpers.h"
#include "Matrix/Vector/vector.h"

Matrix_Statemanager_State matrix_statemanager_state_construct()
{
	Matrix_Statemanager_State state;
	state.core = matrix_statemanager_state_core_construct();
	state.is_loadet = false;
	state.state_data = NULL;

	return state;
}

void matrix_statemanager_state_destruct(Matrix_Statemanager_State* const state)
{
	if (NULL == state)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

Matrix_Statemanager matrix_statemanager_construct()
{
	Matrix_Statemanager statemanager;
	statemanager.states_vec_all = matrix_vector_construct(sizeof(Matrix_Statemanager_State), 1);
	MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager.states_vec_all) = matrix_statemanager_state_construct();
	statemanager.state_index_top = 0;
	statemanager.statemanager_settings = matrix_statemanager_settings_construct();
	statemanager.logger = NULL;
	statemanager.data = NULL;

	return statemanager;
}

void matrix_statemanager_destruct(Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_statemanager_settings_construct(&statemanager->statemanager_settings);
		matrix_vector_destruct(&statemanager->states_vec_all);
	}
}

void matrix_statemanager_init(Matrix_Logger* const logger, Matrix_Data* const data, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		statemanager->logger = logger;
		statemanager->data = data;

		MTRX_CORE_LOG("statemanager: initialisation", MATRIX_LOGGER_LEVEL_INFO, statemanager->logger);
	}
}

void matrix_statemanager_update(Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		double delta = 0;

		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_update)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_update(delta, &MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).state_data, statemanager->data);		
		}
	}
}

void matrix_statemanager_draw2d(Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_draw2d)
		{
			//nothing
		}
		else
		{
			MTRX_STATEMANAGER_LOG("statemanager: %s_state draw2d", statemanager->state_index_top, statemanager);

			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_draw2d(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).state_data, statemanager->data);
		}
	}
}

void matrix_statemanager_draw3d(Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_draw3d)
		{
			//nothing
		}
		else
		{
			MTRX_STATEMANAGER_LOG("statemanager: %s_state draw3d", statemanager->state_index_top, statemanager);

			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_draw3d(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).state_data, statemanager->data);
		}
	}
}

void matrix_statemanager_shutdown(Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp("", MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.name))
		{
			if (MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).is_loadet)
			{
				//nothing
			}
			else
			{
				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_load)
				{
					//nothing
				}
				else
				{
					MTRX_STATEMANAGER_LOG("statemanager: %s_state load", 0, statemanager);

					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_load(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
				}

				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).is_loadet = true;
			}

			if (0 == statemanager->state_index_top)
			{
				//nothing
			}
			else
			{
 				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_leave)
				{
					//nothing
				}
				else
				{
					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_leave(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).state_data, statemanager->data);

					MTRX_STATEMANAGER_LOG("statemanager: %s_state leave", statemanager->state_index_top, statemanager);
				}

				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_enter)
				{
					//nothing
				}
				else
				{
					MTRX_STATEMANAGER_LOG("statemanager: %s_state enter", 0, statemanager);

					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_enter(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
				}

				statemanager->state_index_top = 0;
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_MISSING_DEFAULT;
		}

		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_leave)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_leave(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);

			MTRX_STATEMANAGER_LOG("statemanager: %s_state leave", 0, statemanager);
		}

		for (size_t i = matrix_vector_capacity(statemanager->states_vec_all); i > 0; i--)
		{
			if (MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).is_loadet)
			{
				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).core.on_unload)
				{
					//nothing
				}
				else
				{
					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).core.on_unload(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).state_data, statemanager->data);

					MTRX_STATEMANAGER_LOG("statemanager: %s_state unload", i - 1, statemanager);
				}

				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).is_loadet = false;
			}
		}

		for (size_t i = matrix_vector_capacity(statemanager->states_vec_all); i > 0; i--)
		{
			if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).core.on_destruction)
			{
				//nothing
			}
			else
			{
				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).core.on_destruction(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).state_data, statemanager->data);

				MTRX_STATEMANAGER_LOG("statemanager: %s_state destruction", i - 1, statemanager);
			}

			matrix_statemanager_state_core_destruct(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).core);

		}

		MTRX_CORE_LOG("statemanager: shutdown", MATRIX_LOGGER_LEVEL_INFO, statemanager->logger);
	}
}

void matrix_statemanager_start(Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_load)
		{
			//nothing
		}
		else
		{
			MTRX_STATEMANAGER_LOG("statemanager: %s_state load", 0, statemanager);

			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_load(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
		}

		MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).is_loadet = true;

		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_enter)
		{
			//nothing
		}
		else
		{
			MTRX_STATEMANAGER_LOG("statemanager: %s_state enter", 0, statemanager);

			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).core.on_enter(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
		}
	}
}