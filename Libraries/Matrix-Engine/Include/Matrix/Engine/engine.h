#ifndef ___MTRX___ENGINE_H
#define ___MTRX___ENGINE_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Engine_Info Matrix_Engine_Info;
typedef struct Matrix_Engine_Settings Matrix_Engine_Settings;

Matrix_Engine_Info matrix_engine_info_get(Matrix_Engine* engine);

Matrix_Engine_Settings matrix_engine_settings_construct();
void matrix_engine_settings_destruct(Matrix_Engine_Settings* engine_settings);

void matrix_engine_settings_set(Matrix_Engine_Settings engine_settings, Matrix_Engine* engine);

void matrix_engine_stop(Matrix_Engine* engine);

#endif // !___MTRX___ENGINE_H