#ifndef ___MTRX___STATEMANAGER_DATA_H
#define ___MTRX___STATEMANAGER_DATA_H

typedef struct Matrix_State
{
	const char* name;
	void (*on_creation)();
	void (*on_destruction)();
	void (*on_enter)();
	void (*on_leave)();
	void (*on_update)();
	void (*on_draw2d)();
	void (*on_draw3d)();
} Matrix_Statemanager_State;

#endif // !___MTRX___STATEMANAGER_DATA_H