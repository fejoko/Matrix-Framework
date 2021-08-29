#ifndef ___MTRX___INTERNAL_STATEMANAGER_H
#define ___MTRX___INTERNAL_STATEMANAGER_H

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"
#include "Matrix/Statemanager/statemanager.h"

typedef struct Matrix_Statemanager_State Matrix_Statemanager_State;
typedef struct Matrix_Statemanager Matrix_Statemanager;
typedef struct Matrix_Data Matrix_Data;

Matrix_Statemanager_State matrix_statemanager_state_construct();
void matrix_statemanager_state_destruct(Matrix_Statemanager_State* const state);

Matrix_Statemanager matrix_statemanager_construct();
void matrix_statemanager_destruct(Matrix_Statemanager* const statemanager);

void matrix_statemanager_init(Matrix_Statemanager* const statemanager);
void matrix_statemanager_update(Matrix_Statemanager* const statemanager);
void matrix_statemanager_draw2d(Matrix_Statemanager* const statemanager);
void matrix_statemanager_draw3d(Matrix_Statemanager* const statemanager);
void matrix_statemanager_shutdown(Matrix_Statemanager* const statemanager);

#endif // !___MTRX___INTERNAL_STATEMANAGER_H