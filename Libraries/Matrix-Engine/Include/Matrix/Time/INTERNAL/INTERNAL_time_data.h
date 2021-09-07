#ifndef ___MTRX___INTERNAL_TIME_DATA_H
#define ___MTRX___INTERNAL_TIME_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Time
{
	bool is_recent;
	time_t time_raw;
	struct tm* time_info;
	Matrix_Application* application;
} Matrix_Time;

#endif // !___MTRX___INTERNAL_TIME_DATA_H