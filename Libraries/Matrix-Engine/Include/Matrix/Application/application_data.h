#ifndef ___MTRX___APPLICATION_DATA_H
#define ___MTRX___APPLICATION_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Application Matrix_Application;
typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Statemanager Matrix_Statemanager;

typedef struct Matrix_Application_Core
{
	void (*engine_setup)(Matrix_Engine* engine);
	void (*statemanager_setup)(Matrix_Statemanager* statemanager);
} Matrix_Application_Core;

typedef struct Matrix_Application_Info
{
	const char* application_name;
	const char* build_date;
	const char* build_time;
	uint32_t application_version;
} Matrix_Application_Info;

typedef struct Matrix_Application_Settings
{
	int i;
} Matrix_Application_Settings;

#endif // !___MTRX___APPLICATION_DATA_H