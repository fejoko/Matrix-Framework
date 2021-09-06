#ifndef ___MTRX___INTERNAL_RENDERER_DATA_H
#define ___MTRX___INTERNAL_RENDERER_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Renderer/renderer_data.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Application Matrix_Application;
typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Window Matrix_Window;
typedef struct Matrix_Vector Matrix_Vector;
typedef enum Matrix_Renderer_Shader_Type Matrix_Renderer_Shader_Type;

typedef struct Matrix_Renderer_Shader
{
	Matrix_Renderer_Shader_Type shader_type;
	uint32_t shader_size;
	const char* shader_data;
} Matrix_Renderer_Shader;


typedef struct Matrix_Renderer
{
	bool is_active;
	Matrix_Renderer_Settings renderer_settings;
	Matrix_Engine* engine;
	Matrix_Application* application;
	Matrix_Logger* logger;
	Matrix_Window* window;
	Matrix_Vector* shader_vec;
	void* api_data;
} Matrix_Renderer;

#endif // !___MTRX___INTERNAL_RENDERER_DATA_H