#ifndef ___MTRX___INTERNAL_GLDW_H
#define ___MTRX___INTERNAL_GLDW_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Window Matrix_Window;

void matrix_glfw_construct(Matrix_Window* const window);
void matrix_glfw_init(Matrix_Window* const window);
void matrix_glfw_open(int width, int height, const char* title, Matrix_Window* const window);
void matrix_glfw_update(Matrix_Window* const window);
void matrix_glfw_close(Matrix_Window* const window);
void matrix_glfw_shutdown(Matrix_Window* const window);
void matrix_glfw_destruct(Matrix_Window* const window);

bool matrix_glfw_should_close(Matrix_Window* const window);

#endif // !___MTRX___INTERNAL_GLDW_H