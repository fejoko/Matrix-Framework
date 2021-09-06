#ifndef ___MTRX___ENGINE_DATA_H
#define ___MTRX___ENGINE_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Time Matrix_Time;
typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Window Matrix_Window;
typedef struct Matrix_Renderer Matrix_Renderer;
typedef struct Matrix_Statemanager Matrix_Statemanager;
typedef struct Matrix_Application Matrix_Application;

typedef struct Matrix_Engine_Info
{
	const char* const ENGINE_NAME;
	const char* const BUILD_DATE;
	const char* const BUILD_TIME;
	const uint32_t ENGINE_VERSION;
} Matrix_Engine_Info;

typedef struct Matrix_Engine_Settings
{
	int i;
} Matrix_Engine_Settings;

typedef struct Matrix_Data
{
	Matrix_Engine* engine;
	Matrix_Time* time;
	Matrix_Logger* logger;
	Matrix_Window* window;
	Matrix_Renderer* renderer;
	Matrix_Statemanager* statemanager;
	Matrix_Application* application;
} Matrix_Data;

#endif // !___MTRX___ENGINE_DATA_H