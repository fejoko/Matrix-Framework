#ifndef ___MTRX___RENDERER_H
#define ___MTRX___RENDERER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Renderer Matrix_Renderer;
typedef enum Matrix_Renderer_Shader_Type Matrix_Renderer_Shader_Type;
typedef struct Matrix_Renderer_Settings Matrix_Renderer_Settings;

Matrix_Renderer_Settings matrix_renderer_settings_construct();
void matrix_renderer_settings_destruct(Matrix_Renderer_Settings* const renderer_settings);

void matrix_renderer_settings_set(const Matrix_Renderer_Settings renderer_settings, Matrix_Renderer* const renderer);

void matrix_renderer_start(Matrix_Renderer* const renderer);
void matrix_renderer_stop(Matrix_Renderer* const renderer);

void matrix_renderer_shader_load(const char* shader_path_rel, Matrix_Renderer_Shader_Type shader_type, Matrix_Renderer* const renderer); //shader_path relative to application_path

#endif // !___MTRX___RENDERER_H