#ifndef ___MTRX___INTERNAL_RENDERER_DATA_H
#define ___MTRX___INTERNAL_RENDERER_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Renderer/renderer_data.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Application Matrix_Application;
typedef struct Matrix_Logger Matrix_Logger;

typedef struct Matrix_Renderer
{
	bool is_active;
	Matrix_Renderer_Settings renderer_settings;
	Matrix_Engine* engine;
	Matrix_Application* application;
	Matrix_Logger* logger;
	void* api_data;
} Matrix_Renderer;

#endif // !___MTRX___INTERNAL_RENDERER_DATA_H