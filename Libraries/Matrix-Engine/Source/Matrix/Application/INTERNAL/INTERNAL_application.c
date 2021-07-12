#include "Matrix/Application/INTERNAL/INTERNAL_application.h"

#include "Matrix/Application/INTERNAL/INTERNAL_application_data.h"
#include "Matrix/Core/core.h"

Matrix_Application matrix_applicatione_construct()
{
	Matrix_Application application;
	application.application_core = matrix_application_core_construct();
	application.application_info = matrix_application_info_construct();
	application.application_settings = matrix_application_settings_construct();

	return application;
}

void matrix_application_destruct(Matrix_Application* application)
{
	matrix_application_settings_destruct(&application->application_settings);
	matrix_application_info_destruct(&application->application_info);
	matrix_application_core_destruct(&application->application_core);
}