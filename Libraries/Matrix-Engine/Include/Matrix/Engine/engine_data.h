#ifndef ___MTRX___ENGINE_DATA_H
#define ___MTRX___ENGINE_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

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

#endif // !___MTRX___ENGINE_DATA_H