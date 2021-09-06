#ifndef ___MTRX___ENGINE_H
#define ___MTRX___ENGINE_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Engine_Info Matrix_Engine_Info;
typedef struct Matrix_Engine_Settings Matrix_Engine_Settings;

Matrix_Engine_Info matrix_engine_info_get(const Matrix_Engine* const engine);

Matrix_Engine_Settings matrix_engine_settings_construct();
void matrix_engine_settings_destruct(Matrix_Engine_Settings* const engine_settings);

void matrix_engine_settings_set(const Matrix_Engine_Settings engine_settings, Matrix_Engine* engine);

void matrix_engine_stop(Matrix_Engine* const engine);
bool matrix_engine_stop_is(const Matrix_Engine* const engine);

#endif // !___MTRX___ENGINE_H