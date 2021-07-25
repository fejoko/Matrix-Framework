#ifndef ___MTRX___INTERNAL_STATEMANAGER_DATA_H
#define ___MTRX___INTERNAL_STATEMANAGER_DATA_H

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"
#include "Matrix/Statemanager/statemanager_data.h"

typedef struct Matrix_Vector Matrix_Vector;

typedef struct Matrix_Statemanager_State
{
	Matrix_Statemanager_State_Core core;
	bool is_loadet;
} Matrix_Statemanager_State;

typedef struct Matrix_Statemanager
{
	Matrix_Vector* states_vec_all;
	size_t state_index_top;
	bool state_default_pushed;
} Matrix_Statemanager;

#endif // !___MTRX___INTERNAL_STATEMANAGER_DATA_H