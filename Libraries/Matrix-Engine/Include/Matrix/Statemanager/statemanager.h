#ifndef ___MTRX___STATEMANAGER_H
#define ___MTRX___STATEMANAGER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_State Matrix_State;
typedef struct Matrix_Statemanager Matrix_Statemanager;

Matrix_State matrix_statemanager_state_construct();
void matrix_statemanager_state_destruct(Matrix_State* state);

void matrix_statemanager_state_push(Matrix_State state, Matrix_Statemanager* statemanager);
void matrix_statemanager_state_push_default(Matrix_State state, Matrix_Statemanager* statemanager);

void matrix_statemanager_state_enter(const char* state_name, Matrix_Statemanager* statemanager);

#endif // !___MTRX___STATEMANAGER_H