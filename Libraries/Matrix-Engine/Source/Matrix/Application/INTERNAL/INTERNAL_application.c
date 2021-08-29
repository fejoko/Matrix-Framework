#include "Matrix/Application/INTERNAL/INTERNAL_application.h"

#include "Matrix/Application/INTERNAL/INTERNAL_application_data.h"
#include "Matrix/Core/core.h"
#include "Matrix/Core/error.h"

Matrix_Application matrix_applicatione_construct()
{
	Matrix_Application application;
	application.application_core = matrix_application_core_construct();
	application.application_info = matrix_application_info_construct();
	application.application_settings = matrix_application_settings_construct();
	application.app_data = NULL;

	return application;
}

void matrix_application_destruct(Matrix_Application* const application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_application_settings_destruct(&application->application_settings);
		matrix_application_info_destruct(&application->application_info);
		matrix_application_core_destruct(&application->application_core);
	}
}