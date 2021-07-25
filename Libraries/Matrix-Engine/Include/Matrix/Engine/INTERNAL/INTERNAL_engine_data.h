#ifndef ___MTRX___INTERNAL_ENGINE_DATA_H
#define ___MTRX___INTERNAL_ENGINE_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Application/INTERNAL/INTERNAL_application_data.h"
#include "Matrix/Engine/engine_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"

typedef struct Matrix_Engine
{
	const Matrix_Engine_Info engine_info;
	bool is_stop;
	Matrix_Engine_Settings engine_settings;
	Matrix_Statemanager statemanager;
	Matrix_Application application;
} Matrix_Engine;

#endif // !___MTRX___INTERNAL_ENGINE_DATA_H