#ifndef ___MTRX___RENDERER_DATA_H
#define ___MTRX___RENDERER_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef enum Matrix_Renderer_Api
{
	MATRIX_RENDERER_API_NONE,
	MATRIX_RENDERER_API_VULKAN,
	MATRIX_RENDERER_API_OPENGL,
} Matrix_Renderer_Api;

typedef enum Matrix_Renderer_Shader_Type
{
	MATRIX_RENDERER_SHADER_TYPE_VERTEX,
	MATRIX_RENDERER_SHADER_TYPE_FRAGMENT,
} Matrix_Renderer_Api;

typedef struct Matrix_Renderer_Settings
{
	Matrix_Renderer_Api renderer_api;
} Matrix_Renderer_Settings;

#endif // !___MTRX___RENDERER_DATA_H