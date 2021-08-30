#include "Matrix/Statemanager/statemanager.h"

#include "Matrix/Engine/engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_errors.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_helpers.h"
#include "Matrix/Vector/vector.h"

Matrix_Statemanager_Settings matrix_statemanager_settings_construct()
{
	Matrix_Statemanager_Settings statemanager_settings;
	statemanager_settings.is_state_logging = false;

	return statemanager_settings;
}

void matrix_statemanager_settings_destruct(Matrix_Statemanager_Settings* const statemanager_settings)
{
	if (NULL == statemanager_settings)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_statemanager_settings_set(Matrix_Statemanager_Settings statemanager_settings, Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		statemanager->statemanager_settings = statemanager_settings;
	}
}

Matrix_Statemanager_State_Core matrix_statemanager_state_core_construct()
{
	Matrix_Statemanager_State_Core state;
	state.name = "";
	state.on_creation = NULL;
	state.on_destruction = NULL;
	state.on_load = NULL;
	state.on_unload = NULL;
	state.on_enter = NULL;
	state.on_leave = NULL;
	state.on_update = NULL;
	state.on_draw2d = NULL;
	state.on_draw3d = NULL;

	return state;
}

void matrix_statemanager_state_core_destruct(Matrix_Statemanager_State_Core* const state_core)
{
	if (NULL == state_core)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_statemanager_state_create(const Matrix_Statemanager_State_Core state_core, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp(state_core.name, ""))
		{
			bool found = false;
			for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
			{
				if (strcmp(state_core.name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).core.name))
				{
					//nothing
				}
				else
				{
					found = true;
				}
			}

			if (found)
			{
				MTRX_ERROR_STATEMANAGER_NOTUNIQUE_STATE_NAME;
			}
			else
			{
				Matrix_Statemanager_State state = matrix_statemanager_state_construct();
				state.core = state_core;
				matrix_vector_push_back(MTRX_VECTOR_ELEMENT(state), statemanager->states_vec_all);

				if (NULL == state_core.on_creation)
				{
					//nothing
				}
				else
				{
					matrix_statemanager_log("statemanager: %s_state creation", matrix_vector_capacity(statemanager->states_vec_all) - 1, statemanager);

					state_core.on_creation(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, matrix_vector_capacity(statemanager->states_vec_all) - 1, statemanager->states_vec_all).state_data, statemanager->data);
				}
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

void matrix_statemanager_state_create_default(const Matrix_Statemanager_State_Core state_core, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp(state_core.name, ""))
		{
			bool found = false;
			for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
			{
				if (strcmp(state_core.name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).core.name))
				{
					//nothing
				}
				else
				{
					found = true;
				}
			}

			if (found)
			{
				MTRX_ERROR_STATEMANAGER_NOTUNIQUE_STATE_NAME;
			}
			else
			{
				Matrix_Statemanager_State state = matrix_statemanager_state_construct();
				state.core = state_core;
				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all) = state;

				if (NULL == state_core.on_creation)
				{
					//nothing
				}
				else
				{
					matrix_statemanager_log("statemanager: %s_state creation", 0, statemanager);

					state_core.on_creation(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
				}
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

void matrix_statemanager_state_load(const char* state_name, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		bool found = false;
		size_t index_new = 0;
		for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
		{
			if (strcmp(state_name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).core.name))
			{
				//nothing
			}
			else
			{
				found = true;
				index_new = i;
			}
		}

		if (found)
		{
			if (MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).is_loadet)
			{
				MTRX_ERROR_STATEMANAGER_STATE_LOAD_ALREADY;
			}
			else
			{
				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).core.on_load)
				{
					//nothing
				}
				else
				{
					matrix_statemanager_log("statemanager: %s_state load", index_new, statemanager);

					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).core.on_load(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
				}
			}

			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).is_loadet = true;
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

void matrix_statemanager_state_unload(const char* state_name, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		bool found = false;
		size_t index_new = 0;
		for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
		{
			if (strcmp(state_name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).core.name))
			{
				//nothing
			}
			else
			{
				found = true;
				index_new = i;
			}
		}

		if (found)
		{
			if (MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).is_loadet)
			{
				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_unload)
				{
					//nothing
				}
				else
				{
					matrix_statemanager_log("statemanager: %s_state unload", statemanager->state_index_top, statemanager);

					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_unload(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
				}
			}
			else
			{
				MTRX_ERROR_STATEMANAGER_STATE_LOAD_NOT;
			}

			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).is_loadet = false;
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

bool matrix_statemanager_state_load_is(const char* state_name, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		bool found = false;
		size_t index_new = 0;
		for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
		{
			if (strcmp(state_name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).core.name))
			{
				//nothing
			}
			else
			{
				found = true;
				index_new = i;
			}
		}

		if (found)
		{
			if (MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).is_loadet)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

void matrix_statemanager_state_enter(const char* state_name, Matrix_Statemanager* const statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		bool found = false;
		size_t index_new = 0;
		for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
		{
			if (strcmp(state_name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).core.name))
			{
				//nothing
			}
			else
			{
				found = true;
				index_new = i;
			}
		}

		if (found)
		{
			if (MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).is_loadet)
			{
				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_leave)
				{
					//nothing
				}
				else
				{
					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).core.on_leave(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);

					matrix_statemanager_log("statemanager: %s_state leave", statemanager->state_index_top, statemanager);
				}

				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).core.on_enter)
				{
					//nothing
				}
				else
				{
					matrix_statemanager_log("statemanager: %s_state enter", index_new, statemanager);

					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).core.on_enter(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).state_data, statemanager->data);
				}

				statemanager->state_index_top = index_new;
			}
			else
			{
				MTRX_ERROR_STATEMANAGER_STATE_LOAD_NOT;
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}