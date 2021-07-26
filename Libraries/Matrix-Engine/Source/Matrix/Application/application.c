#include "Matrix/Application/application.h"

#include "Matrix/Application/INTERNAL/INTERNAL_application_data.h"
#include "Matrix/Core/core.h"
#include "Matrix/Core/error.h"

Matrix_Application_Core matrix_application_core_construct()
{
	Matrix_Application_Core application_core;
	application_core.engine_setup = NULL;
	application_core.statemanager_setup = NULL;

	return application_core;
}

void matrix_application_core_destruct(Matrix_Application_Core* application_core)
{

}

Matrix_Application_Info matrix_application_info_construct()
{
	Matrix_Application_Info application_info;
	application_info.application_name = "";
	application_info.build_date = "";
	application_info.build_time = "";
	application_info.application_version = MTRX_VERSION_MAKE(0, 0, 0, 0);

	return application_info;
}

void matrix_application_info_destruct(Matrix_Application_Info* application_info)
{

}

Matrix_Application_Settings matrix_application_settings_construct()
{
	Matrix_Application_Settings application_settings;
	application_settings.i = 0;

	return application_settings;
}

void matrix_application_settings_destruct(Matrix_Application_Settings* application_settings)
{

}

void matrix_application_core_set(Matrix_Application_Core application_core, Matrix_Application* application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		application->application_core = application_core;
	}
}

void matrix_application_info_set(Matrix_Application_Info application_info, Matrix_Application* application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		application->application_info = application_info;
	}
}

void matrix_application_settings_set(Matrix_Application_Settings application_settings, Matrix_Application* application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		application->application_settings = application_settings;
	}
}

void* matrix_application_data_get(Matrix_Application* application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return application->app_data;
	}
}