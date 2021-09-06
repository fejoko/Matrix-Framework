#ifndef ___MTRX___INTERNAL_WINDOW_DATA_H
#define ___MTRX___INTERNAL_WINDOW_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Window/window_data.h"

typedef struct Matrix_Logger Matrix_Logger;

typedef struct Matrix_Window
{
	bool is_opened;
	Matrix_Window_Settings window_settings;
	Matrix_Logger* logger;
	uint32_t width;
	uint32_t height;
	void* api_data;
} Matrix_Window;

#endif // !___MTRX___INTERNAL_WINDOW_DATA_H