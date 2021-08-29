#ifndef ___TWLT___TWILIGHT_H
#define ___TWLT___TWILIGHT_H

#include "Matrix/matrix.h"

void twilight_engine_setup(Matrix_Engine* engine);
void twilight_logger_setup(Matrix_Logger* logger);
void twilight_statemanager_setup(Matrix_Statemanager* statemanager);

void twilight_state_default_on_creation(void** state_data, Matrix_Data* data);
void twilight_state_default_on_destruction(void** state_data, Matrix_Data* data);
void twilight_state_default_on_load(void** state_data, Matrix_Data* data);
void twilight_state_default_on_unload(void** state_data, Matrix_Data* data);
void twilight_state_default_on_enter(void** state_data, Matrix_Data* data);
void twilight_state_default_on_leave(void** state_data, Matrix_Data* data);
void twilight_state_default_on_update(double delta, void** state_data, Matrix_Data* data);
void twilight_state_default_on_draw2d(void** state_data, Matrix_Data* data);
void twilight_state_default_on_draw3d(void** state_data, Matrix_Data* data);

#endif // !___TWLT___TWILIGHT_H