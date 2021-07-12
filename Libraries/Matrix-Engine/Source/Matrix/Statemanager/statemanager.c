#include "Matrix/Statemanager/statemanager.h"

#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_errors.h"
#include "Matrix/Vector/vector.h"

Matrix_Statemanager_State matrix_statemanager_state_construct()
{
	Matrix_Statemanager_State state;
	state.name = "";
	state.on_creation = NULL;
	state.on_destruction = NULL;
	state.on_enter = NULL;
	state.on_leave = NULL;
	state.on_update = NULL;
	state.on_draw2d = NULL;
	state.on_draw3d = NULL;

	return state;
}

void matrix_statemanager_state_destruct(Matrix_Statemanager_State* state)
{
	if (NULL == state)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		
	}
}

void matrix_statemanager_state_push(Matrix_Statemanager_State state, Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp(state.name, ""))
		{
			bool found = false;
			for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
			{
				if (strcmp(state.name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).name))
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
				matrix_vector_push_back(&state, statemanager->states_vec_all);

				if (NULL == state.on_creation)
				{
					//nothing
				}
				else
				{
					state.on_creation();
				}
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

void matrix_statemanager_state_push_default(Matrix_Statemanager_State state, Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp(state.name, ""))
		{
			bool found = false;
			for (size_t i = 0; i < matrix_vector_capacity(statemanager->states_vec_all); i++)
			{
				if (strcmp(state.name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).name))
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
				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all) = state;

				if (NULL == state.on_creation)
				{
					//nothing
				}
				else
				{
					state.on_creation();
				}
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}

void matrix_statemanager_state_enter(const char* state_name, Matrix_Statemanager* statemanager)
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
			if (strcmp(state_name, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i, statemanager->states_vec_all).name))
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
			if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_leave)
			{
				//nothing
			}
			else
			{
				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_leave();
			}

			if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).on_enter)
			{
				//nothing
			}
			else
			{
				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, index_new, statemanager->states_vec_all).on_enter();
			}

			statemanager->state_index_top = index_new;
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME;
		}
	}
}