#ifndef ___MTRX___STATEMANAGER_H
#define ___MTRX___STATEMANAGER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Statemanager_State_Core Matrix_Statemanager_State_Core;
typedef struct Matrix_Statemanager Matrix_Statemanager;

Matrix_Statemanager_State_Core matrix_statemanager_state_core_construct();
void matrix_statemanager_state_core_destruct(Matrix_Statemanager_State_Core* state_core);

void matrix_statemanager_state_create(Matrix_Statemanager_State_Core state_core, Matrix_Statemanager* statemanager);
void matrix_statemanager_state_create_default(Matrix_Statemanager_State_Core state_core, Matrix_Statemanager* statemanager);

void matrix_statemanager_state_load(const char* state_name, Matrix_Statemanager* statemanager);
void matrix_statemanager_state_unload(const char* state_name, Matrix_Statemanager* statemanager);

bool matrix_statemanager_state_load_is(const char* state_name, Matrix_Statemanager* statemanager);

void matrix_statemanager_state_enter(const char* state_name, Matrix_Statemanager* statemanager);

#endif // !___MTRX___STATEMANAGER_H