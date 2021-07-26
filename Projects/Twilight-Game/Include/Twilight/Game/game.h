#ifndef ___TWLT___GAME_H
#define ___TWLT___GAME_H

#include "Matrix/matrix.h"

void twilight_state_game_on_creation(void** state_data, Matrix_Data* data);
void twilight_state_game_on_destruction(void** state_data, Matrix_Data* data);
void twilight_state_game_on_load(void** state_data, Matrix_Data* data);
void twilight_state_game_on_unload(void** state_data, Matrix_Data* data);
void twilight_state_game_on_enter(void** state_data, Matrix_Data* data);
void twilight_state_game_on_leave(void** state_data, Matrix_Data* data);
void twilight_state_game_on_update(double delta, void** state_data, Matrix_Data* data);
void twilight_state_game_on_draw2d(void** state_data, Matrix_Data* data);
void twilight_state_game_on_draw3d(void** state_data, Matrix_Data* data);

#endif // !___TWLT___GAME_H