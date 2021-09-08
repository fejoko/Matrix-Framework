#ifndef ___MTRX___INTERNAL_GLDW_H
#define ___MTRX___INTERNAL_GLDW_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Window/INTERNAL/Glfw/INTERNAL_glfw_data.h"

typedef struct Matrix_Window Matrix_Window;

void matrix_glfw_construct(Matrix_Window* const window);
void matrix_glfw_init(Matrix_Window* window);
void matrix_glfw_open(int width, int height, const char* title, Matrix_Window* const window);
void matrix_glfw_update(Matrix_Window* const window);
void matrix_glfw_close(Matrix_Window* const window);
void matrix_glfw_shutdown(Matrix_Window* const window);
void matrix_glfw_destruct(Matrix_Window* const window);

bool matrix_glfw_should_close(Matrix_Window* const window);

void* matrix_glfw_raw_get(Matrix_Window* const window);

void matrix_glfw_onResize(GLFWwindow* glfw_window, int width_new, int height_new);

#endif // !___MTRX___INTERNAL_GLDW_H