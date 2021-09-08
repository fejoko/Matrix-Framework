#ifndef ___MTRX___WINDOW_DATA_H
#define ___MTRX___WINDOW_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef enum Matrix_Window_Api
{
	MATRIX_WINDOW_API_NONE,
	MATRIX_WINDOW_API_GLFW,
	MATRIX_WINDOW_API_WINDOWS,
} Matrix_Window_Api;

typedef struct Matrix_Window_Settings
{
	Matrix_Window_Api window_api;
	int window_width_min;
	int window_height_min;
} Matrix_Window_Settings;

#endif // !___MTRX___WINDOW_DATA_H