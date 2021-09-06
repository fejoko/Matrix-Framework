#ifndef ___MTRX___APPLICATION_DATA_H
#define ___MTRX___APPLICATION_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Application Matrix_Application;
typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Time Matrix_Time;
typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Window Matrix_Window;
typedef struct Matrix_Renderer Matrix_Renderer;
typedef struct Matrix_Statemanager Matrix_Statemanager;

typedef struct Matrix_Application_Core
{
	void (*engine_setup)(Matrix_Engine* engine);
	void (*logger_setup)(Matrix_Logger* logger);
	void (*window_setup)(Matrix_Window* window);
	void (*renderer_setup)(Matrix_Renderer* renderer);
	void (*statemanager_setup)(Matrix_Statemanager* statemanager);
} Matrix_Application_Core;

typedef struct Matrix_Application_Info
{
	const char* application_name;
	const char* build_date;
	const char* build_time;
	uint32_t application_version;
	const char* application_path_abs;
} Matrix_Application_Info;

typedef struct Matrix_Application_Settings
{
	bool is_prelogging;
} Matrix_Application_Settings;

#endif // !___MTRX___APPLICATION_DATA_H