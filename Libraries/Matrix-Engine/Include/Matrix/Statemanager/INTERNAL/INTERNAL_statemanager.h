#ifndef ___MTRX___INTERNAL_STATEMANAGER_H
#define ___MTRX___INTERNAL_STATEMANAGER_H

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"
#include "Matrix/Statemanager/statemanager.h"

typedef struct Matrix_Statemanager Matrix_Statemanager;

Matrix_Statemanager matrix_statemanager_construct();
void matrix_statemanager_destruct(Matrix_Statemanager* statemanager);

void matrix_statemanager_init(Matrix_Statemanager* statemanager);
void matrix_statemanager_update(Matrix_Statemanager* statemanager);
void matrix_statemanager_draw2d(Matrix_Statemanager* statemanager);
void matrix_statemanager_draw3d(Matrix_Statemanager* statemanager);
void matrix_statemanager_shutdown(Matrix_Statemanager* statemanager);

void matrix_statemanager_state_enter_default(Matrix_Statemanager* statemanager);

#endif // !___MTRX___INTERNAL_STATEMANAGER_H