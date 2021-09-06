#ifndef ___MTRX___INTERNAL_RENDERER_H
#define ___MTRX___INTERNAL_RENDERER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Application Matrix_Application;
typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Window Matrix_Window;
typedef struct Matrix_Renderer Matrix_Renderer;

Matrix_Renderer matrix_renderer_construct();
void matrix_renderer_destruct(Matrix_Renderer* const renderer);

void matrix_renderer_init(Matrix_Engine* const engine, Matrix_Application* const application, Matrix_Logger* const logger, Matrix_Window* const window, Matrix_Renderer* const renderer);
void matrix_renderer_update(Matrix_Renderer* const renderer);
void matrix_renderer_shutdown(Matrix_Renderer* const renderer);

#endif // !___MTRX___INTERNAL_RENDERER_H