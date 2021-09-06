#ifndef ___MTRX___INTERNAL_ENGINE_DATA_H
#define ___MTRX___INTERNAL_ENGINE_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"
#include "Matrix/Application/INTERNAL/INTERNAL_application_data.h"
#include "Matrix/Engine/engine_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger_data.h"
#include "Matrix/Renderer/INTERNAL/INTERNAL_renderer_data.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Time/INTERNAL/INTERNAL_time_data.h"
#include "Matrix/Window/INTERNAL/INTERNAL_window_data.h"

typedef struct Matrix_Engine
{
	const Matrix_Engine_Info engine_info;
	bool is_stop;
	Matrix_Engine_Settings engine_settings;
	Matrix_Time time_;
	Matrix_Logger logger;
	Matrix_Statemanager statemanager;
	Matrix_Window window;
	Matrix_Renderer renderer;
	Matrix_Application application;
	Matrix_Data data;
} Matrix_Engine;

#endif // !___MTRX___INTERNAL_ENGINE_DATA_H