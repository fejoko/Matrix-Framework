#ifndef ___MTRX___INTERNAL_ENGINE_H
#define ___MTRX___INTERNAL_ENGINE_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Engine Matrix_Engine;

Matrix_Engine matrix_engine_construct();
void matrix_engine_destruct(Matrix_Engine* const engine);

void matrix_engine_run(Matrix_Engine* const engine);

#endif // !___MTRX___INTERNAL_ENGINE_H