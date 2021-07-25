#include "Twilight/Game/game.h"

#include "Matrix/matrix.h"

void twilight_state_game_on_creation()
{
	MTRX_PRINTF("game creation\n");
}

void twilight_state_game_on_destruction()
{
	MTRX_PRINTF("game destruction\n");
}

void twilight_state_game_on_load()
{
	MTRX_PRINTF("game load\n");
}

void twilight_state_game_on_unload()
{
	MTRX_PRINTF("game unload\n");
}

void twilight_state_game_on_enter()
{
	MTRX_PRINTF("game enter\n");
}

void twilight_state_game_on_leave()
{
	MTRX_PRINTF("game leave\n");
}

void twilight_state_game_on_update()
{
	MTRX_PRINTF("game update\n");
}

void twilight_state_game_on_draw2d()
{
	MTRX_PRINTF("game draw2d\n");
}

void twilight_state_game_on_draw3d()
{
	MTRX_PRINTF("game draw3d\n");
}