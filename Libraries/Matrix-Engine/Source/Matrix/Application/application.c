#include "Matrix/Application/application.h"

#include "Matrix/Application/INTERNAL/INTERNAL_application_data.h"
#include "Matrix/Core/core.h"
#include "Matrix/Core/error.h"

Matrix_Application_Core matrix_application_core_construct()
{
	Matrix_Application_Core application_core;
	application_core.engine_setup = NULL;
	application_core.logger_setup = NULL;
	application_core.window_setup = NULL;
	application_core.renderer_setup = NULL;
	application_core.statemanager_setup = NULL;

	return application_core;
}

void matrix_application_core_destruct(Matrix_Application_Core* const application_core)
{
	if (NULL == application_core)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

Matrix_Application_Info matrix_application_info_construct()
{
	Matrix_Application_Info application_info;
	application_info.application_name = "";
	application_info.build_date = "";
	application_info.build_time = "";
	application_info.application_version = MTRX_VERSION_MAKE(0, 0, 0, 0);
	application_info.application_path_abs = "";

	return application_info;
}

void matrix_application_info_destruct(Matrix_Application_Info* const application_info)
{
	if (NULL == application_info)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

Matrix_Application_Settings matrix_application_settings_construct()
{
	Matrix_Application_Settings application_settings;
	application_settings.is_prelogging = false;

	return application_settings;
}

void matrix_application_settings_destruct(Matrix_Application_Settings* const application_settings)
{
	if (NULL == application_settings)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_application_core_set(const Matrix_Application_Core application_core, Matrix_Application* const application)
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

void matrix_application_info_set(const Matrix_Application_Info application_info, Matrix_Application* const application)
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

void matrix_application_settings_set(const Matrix_Application_Settings application_settings, Matrix_Application* const application)
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

void* matrix_application_data_get(const Matrix_Application* const application)
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

const char* matrix_application_path_abs_get(const Matrix_Application* const application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return application->application_info.application_path_abs;
	}
}