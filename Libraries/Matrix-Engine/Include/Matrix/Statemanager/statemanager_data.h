#ifndef ___MTRX___STATEMANAGER_DATA_H
#define ___MTRX___STATEMANAGER_DATA_H

typedef struct Matrix_Data Matrix_Data;

typedef struct Matrix_Statemanager_State_Core
{
	const char* name;
	void (*on_creation)(void** state_data, Matrix_Data* data);
	void (*on_destruction)(void** state_data, Matrix_Data* data);
	void (*on_load)(void** state_data, Matrix_Data* data);
	void (*on_unload)(void** state_data, Matrix_Data* data);
	void (*on_enter)(void** state_data, Matrix_Data* data);
	void (*on_leave)(void** state_data, Matrix_Data* data);
	void (*on_update)(double delta, void** state_data, Matrix_Data* data);
	void (*on_draw2d)(void** state_data, Matrix_Data* data);
	void (*on_draw3d)(void** state_data, Matrix_Data* data);
} Matrix_Statemanager_State_Core;

typedef struct Matrix_Statemanager_Settings
{
	bool is_draw2d;
	bool is_draw3d;
} Matrix_Statemanager_Settings;

#endif // !___MTRX___STATEMANAGER_DATA_H