#include "Twilight/Game/game.h"

#include "Matrix/matrix.h"

void twilight_state_game_on_creation(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game creation\n");
}

void twilight_state_game_on_destruction(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game destruction\n");
}

void twilight_state_game_on_load(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game load\n");
}

void twilight_state_game_on_unload(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game unload\n");
}

void twilight_state_game_on_enter(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game enter\n");
}

void twilight_state_game_on_leave(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game leave\n");
}

void twilight_state_game_on_update(double delta, void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game update\n");
}

void twilight_state_game_on_draw2d(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game draw2d\n");
}

void twilight_state_game_on_draw3d(void** state_data, Matrix_Data* data)
{
	MTRX_PRINTF("game draw3d\n");
}