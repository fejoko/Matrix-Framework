#ifndef ___MTRX___INTERNAL_APPLICATION_DATA_H
#define ___MTRX___INTERNAL_APPLICATION_DATA_H

#include "Matrix/Application/application_data.h"
#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Application
{
	Matrix_Application_Core application_core;
	Matrix_Application_Info application_info;
	Matrix_Application_Settings application_settings;
} Matrix_Application;

#endif // !___MTRX___INTERNAL_APPLICATION_DATA_H