#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"

#include "Matrix/Core/error.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_errors.h"
#include "Matrix/Vector/vector.h"

void matrix_INTERNAL_statemanager_state_enter_default(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (strcmp("", MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).name))
		{
			if (0 == statemanager->state_index_top)
			{
				//nothing
			}
			else
			{
				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_leave)
				{
					//nothing
				}
				else
				{
					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_leave();
				}

				if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).on_enter)
				{
					//nothing
				}
				else
				{
					MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager->states_vec_all).on_enter();
				}

				statemanager->state_index_top = 0;
			}
		}
		else
		{
			MTRX_ERROR_STATEMANAGER_MISSING_DEFAULT;
		}
	}
}

Matrix_Statemanager matrix_statemanager_construct()
{
	Matrix_Statemanager statemanager;
	statemanager.states_vec_all = matrix_vector_construct(sizeof(Matrix_Statemanager_State), 1);
	MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, 0, statemanager.states_vec_all) = matrix_statemanager_state_construct();
	statemanager.state_index_top = 0;

	return statemanager;
}

void matrix_statemanager_destruct(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_vector_destruct(statemanager->states_vec_all);
	}
}

void matrix_statemanager_init(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_enter)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_enter();
		}
	}
}

void matrix_statemanager_update(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_update)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_update();
		}
	}
}

void matrix_statemanager_draw2d(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_draw2d)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_draw2d();
		}
	}
}

void matrix_statemanager_draw3d(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_draw3d)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_draw3d();
		}
	}
}

void matrix_statemanager_shutdown(Matrix_Statemanager* statemanager)
{
	if (NULL == statemanager)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_INTERNAL_statemanager_state_enter_default(statemanager);

		if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_leave)
		{
			//nothing
		}
		else
		{
			MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, statemanager->state_index_top, statemanager->states_vec_all).on_leave();
		}

		for (size_t i = matrix_vector_capacity(statemanager->states_vec_all); i > 0; i--)
		{
			if (NULL == MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).on_destruction)
			{
				//nothing
			}
			else
			{
				MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all).on_destruction();
			}

			matrix_statemanager_state_destruct(&MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, i - 1, statemanager->states_vec_all));
		}
	}
}