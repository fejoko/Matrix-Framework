#include "Twilight/twilight.h"

void matrix_application_attach(Matrix_Application* application)
{
	Matrix_Application_Core application_core = matrix_application_core_construct();
	application_core.engine_setup = twilight_engine_setup;
	application_core.statemanager_setup = twilight_statemanager_setup;
	matrix_application_core_set(application_core, application);
	matrix_application_core_destruct(&application_core);

	Matrix_Application_Info application_info = matrix_application_info_construct();
	application_info.application_name = "twilight";
	application_info.build_date = __DATE__;
	application_info.build_time = __TIME__;
	application_info.application_version = MTRX_VERSION_MAKE(0, 0, 1, 0);
	matrix_application_info_set(application_info, application);
	matrix_application_info_destruct(&application_info);

	Matrix_Application_Settings application_settings = matrix_application_settings_construct();
	application_settings.i = 0;
	matrix_application_settings_set(application_settings, application);
	matrix_application_settings_destruct(&application_settings);
}

void twilight_engine_setup(Matrix_Engine* engine)
{
	Matrix_Engine_Info engine_info = matrix_engine_info_get(engine);

	Matrix_Engine_Settings engine_settings = matrix_engine_settings_construct();
	engine_settings.i = 0;
	matrix_engine_settings_set(engine_settings, engine);
	matrix_engine_settings_destruct(&engine_settings);

	matrix_engine_stop(engine);
}

void twilight_statemanager_setup(Matrix_Statemanager* statemanager)
{
	Matrix_Statemanager_State state_default = matrix_statemanager_state_construct();
	state_default.name = "default";
	state_default.on_creation = twilight_state_default_on_creation;
	state_default.on_destruction = twilight_state_default_on_destruction;
	state_default.on_enter = twilight_state_default_on_enter;
	state_default.on_leave = twilight_state_default_on_leave;
	state_default.on_update = twilight_state_default_on_update;
	state_default.on_draw2d = twilight_state_default_on_draw2d;
	state_default.on_draw3d = twilight_state_default_on_draw3d;
	matrix_statemanager_state_push_default(state_default, statemanager);
	matrix_statemanager_state_destruct(&state_default);
}

void twilight_state_default_on_creation()
{
	MTRX_PRINTF("creation\n");
}

void twilight_state_default_on_destruction()
{
	MTRX_PRINTF("destruction\n");
}

void twilight_state_default_on_enter()
{
	MTRX_PRINTF("enter\n");
}

void twilight_state_default_on_leave()
{
	MTRX_PRINTF("leave\n");
}

void twilight_state_default_on_update()
{
	MTRX_PRINTF("update\n");
}

void twilight_state_default_on_draw2d()
{
	MTRX_PRINTF("draw2d\n");
}

void twilight_state_default_on_draw3d()
{
	MTRX_PRINTF("draw3d\n");
}