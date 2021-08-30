#ifndef ___MTRX___STATEMANAGER_H
#define ___MTRX___STATEMANAGER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Statemanager_Settings Matrix_Statemanager_Settings;
typedef struct Matrix_Statemanager_State_Core Matrix_Statemanager_State_Core;
typedef struct Matrix_Statemanager Matrix_Statemanager;
typedef struct Matrix_State Matrix_State;

Matrix_Statemanager_Settings matrix_statemanager_settings_construct();
void matrix_statemanager_settings_destruct(Matrix_Statemanager_Settings* const statemanager_settings);

void matrix_statemanager_settings_set(Matrix_Statemanager_Settings statemanager_settings, Matrix_Statemanager* statemanager);

Matrix_Statemanager_State_Core matrix_statemanager_state_core_construct();
void matrix_statemanager_state_core_destruct(Matrix_Statemanager_State_Core* const state_core);

void matrix_statemanager_state_create(const Matrix_Statemanager_State_Core state_core, Matrix_Statemanager* const statemanager);
void matrix_statemanager_state_create_default(const Matrix_Statemanager_State_Core state_core, Matrix_Statemanager* const statemanager);

void matrix_statemanager_state_load(const char* state_name, Matrix_Statemanager* const statemanager);
void matrix_statemanager_state_unload(const char* state_name, Matrix_Statemanager* const statemanager);

bool matrix_statemanager_state_load_is(const char* state_name, Matrix_Statemanager* const statemanager);

void matrix_statemanager_state_enter(const char* state_name, Matrix_Statemanager* const statemanager);

#endif // !___MTRX___STATEMANAGER_H