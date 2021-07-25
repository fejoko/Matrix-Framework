#ifndef ___TWLT___TWILIGHT_H
#define ___TWLT___TWILIGHT_H

#include "Matrix/matrix.h"

void twilight_engine_setup(Matrix_Engine* engine);
void twilight_statemanager_setup(Matrix_Statemanager* statemanager);

void twilight_state_default_on_creation();
void twilight_state_default_on_destruction();
void twilight_state_default_on_load();
void twilight_state_default_on_unload();
void twilight_state_default_on_enter();
void twilight_state_default_on_leave();
void twilight_state_default_on_update();
void twilight_state_default_on_draw2d();
void twilight_state_default_on_draw3d();

#endif // !___TWLT___TWILIGHT_H