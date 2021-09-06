#ifndef ___MTRX___RENDERER_H
#define ___MTRX___RENDERER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Renderer Matrix_Renderer;
typedef struct Matrix_Renderer_Settings Matrix_Renderer_Settings;

Matrix_Renderer_Settings matrix_renderer_settings_construct();
void matrix_renderer_settings_destruct(Matrix_Renderer_Settings* const renderer_settings);

void matrix_renderer_settings_set(const Matrix_Renderer_Settings renderer_settings, Matrix_Renderer* renderer);

void matrix_renderer_start(Matrix_Renderer* const renderer);
void matrix_renderer_stop(Matrix_Renderer* const renderer);

#endif // !___MTRX___RENDERER_H