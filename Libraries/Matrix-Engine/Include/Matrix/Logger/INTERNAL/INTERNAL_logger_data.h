#ifndef ___MTRX___INTERNAL_LOGGER_DATA_H
#define ___MTRX___INTERNAL_LOGGER_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Logger/logger_data.h"

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Time Matrix_Time;

typedef struct Matrix_Logger
{
	Matrix_Logger_Settings logger_settings;
	Matrix_Engine* engine;
	Matrix_Time* time_;
} Matrix_Logger;

#define MTRX_LOGGER_FLAG_CLIENT 0x00
#define MTRX_LOGGER_FLAG_CORE 0x01

#endif // !___MTRX___INTERNAL_LOGGER_DATA_H