#ifndef ___MTRX___INTERNAL_WINDOW_H
#define ___MTRX___INTERNAL_WINDOW_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Window Matrix_Window;

Matrix_Window matrix_window_construct();
void matrix_window_destruct(Matrix_Window* const window);

void matrix_window_init(Matrix_Logger* const logger, Matrix_Window* const window);
void matrix_window_update(Matrix_Window* const window);
void matrix_window_shutdown(Matrix_Window* const window);

#endif // !___MTRX___INTERNAL_WINDOW_H