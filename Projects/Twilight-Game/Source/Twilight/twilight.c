#include "Twilight/twilight.h"

#include "Twilight/Game/game.h"

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
}

void twilight_statemanager_setup(Matrix_Statemanager* statemanager)
{
	Matrix_Statemanager_State_Core state_default = matrix_statemanager_state_core_construct();
	state_default.name = "default";
	state_default.on_creation = twilight_state_default_on_creation;
	state_default.on_destruction = twilight_state_default_on_destruction;
	state_default.on_load = twilight_state_default_on_load;
	state_default.on_unload = twilight_state_default_on_unload;
	state_default.on_enter = twilight_state_default_on_enter;
	state_default.on_leave = twilight_state_default_on_leave;
	state_default.on_update = twilight_state_default_on_update;
	state_default.on_draw2d = twilight_state_default_on_draw2d;
	state_default.on_draw3d = twilight_state_default_on_draw3d;
	matrix_statemanager_state_create_default(state_default, statemanager);
	matrix_statemanager_state_core_destruct(&state_default);

	Matrix_Statemanager_State_Core state_game = matrix_statemanager_state_core_construct();
	state_game.name = "game";
	state_game.on_creation = twilight_state_game_on_creation;
	state_game.on_destruction = twilight_state_game_on_destruction;
	state_game.on_load = twilight_state_game_on_load;
	state_game.on_unload = twilight_state_game_on_unload;
	state_game.on_enter = twilight_state_game_on_enter;
	state_game.on_leave = twilight_state_game_on_leave;
	state_game.on_update = twilight_state_game_on_update;
	state_game.on_draw2d = twilight_state_game_on_draw2d;
	state_game.on_draw3d = twilight_state_game_on_draw3d;
	matrix_statemanager_state_create(state_game, statemanager);
	matrix_statemanager_state_core_destruct(&state_game);
}

void twilight_state_default_on_creation(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default creation\n");
	*state_data = matrix_vector_construct(sizeof(int), 10);
	MTRX_PRINTF("%u\n", matrix_vector_capacity(*state_data));
}

void twilight_state_default_on_destruction(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("%u\n", matrix_vector_capacity(*state_data));
	free(*state_data);
	MTRX_PRINTF("default destruction\n");
}

void twilight_state_default_on_load(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default load\n");
}

void twilight_state_default_on_unload(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default unload\n");
}

void twilight_state_default_on_enter(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default enter\n");
	if (!matrix_engine_stop_is(data->engine))
	{
		matrix_statemanager_state_load("game", data->statemanager);
		matrix_statemanager_state_enter("game", data->statemanager);
		matrix_engine_stop(data->engine);
	}
}

void twilight_state_default_on_leave(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default leave\n");
}

void twilight_state_default_on_update(double delta, void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default update\n");
}

void twilight_state_default_on_draw2d(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default draw2d\n");
}

void twilight_state_default_on_draw3d(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("default draw3d\n");
}