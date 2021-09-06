#ifndef ___MTRX___WINDOW_H
#define ___MTRX___WINDOW_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Window Matrix_Window;
typedef struct Matrix_Window_Settings Matrix_Window_Settings;

Matrix_Window_Settings matrix_window_settings_construct();
void matrix_window_settings_destruct(Matrix_Window_Settings* const window_settings);

void matrix_window_settings_set(const Matrix_Window_Settings window_settings, Matrix_Window* window);

void matrix_window_open(int width, int height, const char* title, Matrix_Window* const window);
void matrix_window_close(Matrix_Window* const window);

bool matrix_window_opened_is(Matrix_Window* const window);
bool matrix_window_should_close(Matrix_Window* const window);

int matrix_window_width_get(Matrix_Window* const window);
int matrix_window_height_get(Matrix_Window* const window);

#endif // !___MTRX___WINDOW_H