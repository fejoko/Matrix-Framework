#ifndef ___MTRX___INTERNAL_WINDOW_H
#define ___MTRX___INTERNAL_WINDOW_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Window/window.h"

typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Renderer Matrix_Renderer;
typedef struct Matrix_Window Matrix_Window;
typedef enum Matrix_Window_Api Matrix_Window_Api;

Matrix_Window matrix_window_construct();
void matrix_window_destruct(Matrix_Window* const window);

void matrix_window_init(Matrix_Logger* const logger, Matrix_Renderer* const renderer, Matrix_Window* const window);
void matrix_window_update(Matrix_Window* const window);
void matrix_window_shutdown(Matrix_Window* const window);

Matrix_Window_Api matrix_window_api_get(Matrix_Window* const window);
void* matrix_window_raw_get(Matrix_Window* const window);

void matrix_window_onResize(int width_new, int height_new, Matrix_Window* const window);

#endif // !___MTRX___INTERNAL_WINDOW_H